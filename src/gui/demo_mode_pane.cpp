// src/gui/demo_mode_pane.cpp — graduation demo flow pane.

#include "demo_mode_pane.h"

#include <QFrame>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QSize>
#include <QSizePolicy>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

namespace aura::gui {

DemoModePane::DemoModePane(QWidget* parent) : QWidget(parent) {
    setObjectName(QStringLiteral("demoModePane"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto* root = new QVBoxLayout(this);

    m_claimLabel = new QLabel(
        tr("AURA masks sensitive reverse-engineering data before LLM/MCP export."),
        this);
    m_claimLabel->setObjectName(QStringLiteral("demoClaimLabel"));
    m_claimLabel->setWordWrap(true);
    m_claimLabel->setMinimumWidth(0);
    root->addWidget(m_claimLabel);

    auto* flowSummary = new QLabel(
        QStringLiteral("1. RE 결과 수집 -> 2. 민감정보 탐지 -> 3. 마스킹 -> 4. LLM 전송 검증"),
        this);
    flowSummary->setObjectName(QStringLiteral("demoFlowSummaryLabel"));
    flowSummary->setWordWrap(true);
    flowSummary->setMinimumWidth(0);
    root->addWidget(flowSummary);

    auto* stageGrid = new QGridLayout;
    stageGrid->addWidget(
        makeStageCard(QStringLiteral("demoStageAnalyze"),
                      tr("1. Analyze"),
                      tr("Load a binary and extract strings/functions.")),
        0, 0);
    stageGrid->addWidget(
        makeStageCard(QStringLiteral("demoStageDetect"),
                      tr("2. Detect"),
                      tr("Find RRN, phone, email, and token-like strings.")),
        0, 1);
    stageGrid->addWidget(
        makeStageCard(QStringLiteral("demoStageMask"),
                      tr("3. Mask"),
                      tr("Show protected values like 900101-1******.")),
        0, 2);
    stageGrid->addWidget(
        makeStageCard(QStringLiteral("demoStageExport"),
                      tr("4. Export"),
                      tr("Send only protected values to LLM/MCP.")),
        0, 3);
    root->addLayout(stageGrid);

    auto* metaGrid = new QGridLayout;
    m_binaryLabel = new QLabel(tr("Binary: not loaded"), this);
    m_binaryLabel->setObjectName(QStringLiteral("demoBinaryLabel"));
    m_engineLabel = new QLabel(tr("Engine: not analyzed"), this);
    m_engineLabel->setObjectName(QStringLiteral("demoEngineLabel"));
    m_summaryLabel =
        new QLabel(tr("Strings: 0 / Protected: 0 / Export rows: 0"), this);
    m_summaryLabel->setObjectName(QStringLiteral("demoSummaryLabel"));
    metaGrid->addWidget(m_binaryLabel, 0, 0);
    metaGrid->addWidget(m_engineLabel, 0, 1);
    metaGrid->addWidget(m_summaryLabel, 1, 0, 1, 2);
    root->addLayout(metaGrid);

    m_sensitiveItemsTable = new QTableWidget(this);
    m_sensitiveItemsTable->setObjectName(QStringLiteral("demoSensitiveItemsTable"));
    m_sensitiveItemsTable->setMinimumWidth(0);
    m_sensitiveItemsTable->setSizePolicy(QSizePolicy::Expanding,
                                         QSizePolicy::Expanding);
    m_sensitiveItemsTable->setColumnCount(4);
    m_sensitiveItemsTable->setHorizontalHeaderLabels(
        {QStringLiteral("종류"),
         QStringLiteral("UI 확인용 원본"),
         QStringLiteral("마스킹"),
         QStringLiteral("LLM 전송")});
    m_sensitiveItemsTable->horizontalHeader()->setStretchLastSection(true);
    root->addWidget(m_sensitiveItemsTable, 2);

    m_exportPreview = new QLabel(
        tr("{\"transmission_policy\":\"protected\",\"original_included\":false,\"items\":[]}"),
        this);
    m_exportPreview->setObjectName(QStringLiteral("demoExportPreview"));
    m_exportPreview->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_exportPreview->setWordWrap(true);
    m_exportPreview->setMinimumWidth(0);
    root->addWidget(m_exportPreview);
}

QWidget* DemoModePane::makeStageCard(const QString& objectName,
                                     const QString& title,
                                     const QString& body) {
    auto* frame = new QFrame(this);
    frame->setObjectName(objectName);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setMinimumWidth(0);
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    auto* layout = new QVBoxLayout(frame);
    auto* titleLabel = new QLabel(title, frame);
    auto* bodyLabel = new QLabel(body, frame);
    bodyLabel->setWordWrap(true);
    titleLabel->setMinimumWidth(0);
    bodyLabel->setMinimumWidth(0);
    layout->addWidget(titleLabel);
    layout->addWidget(bodyLabel);
    return frame;
}

QSize DemoModePane::sizeHint() const {
    return QSize(900, 520);
}

QSize DemoModePane::minimumSizeHint() const {
    // This pane is tabified with the decompile/disassembly dock group. A large
    // minimum width here makes the whole group refuse horizontal splitter moves
    // even when another tab is active.
    return QSize(260, 180);
}

void DemoModePane::setBinaryName(const QString& name) {
    m_binaryLabel->setText(
        tr("Binary: %1").arg(name.isEmpty() ? tr("not loaded") : name));
}

void DemoModePane::setEngineName(const QString& name) {
    m_engineLabel->setText(
        tr("Engine: %1").arg(name.isEmpty() ? tr("not analyzed") : name));
}

void DemoModePane::setSummary(int extractedStrings,
                              int protectedStrings,
                              int exportRows) {
    m_summaryLabel->setText(tr("Strings: %1 / Protected: %2 / Export rows: %3")
                                .arg(extractedStrings)
                                .arg(protectedStrings)
                                .arg(exportRows));
}

void DemoModePane::setSensitiveItems(const QVector<DemoSensitiveItemRow>& rows) {
    m_sensitiveItemsTable->setRowCount(rows.size());
    for (int i = 0; i < rows.size(); ++i) {
        m_sensitiveItemsTable->setItem(
            i, 0, new QTableWidgetItem(rows[i].category));
        m_sensitiveItemsTable->setItem(
            i, 1, new QTableWidgetItem(rows[i].originalValue));
        m_sensitiveItemsTable->setItem(
            i, 2, new QTableWidgetItem(rows[i].maskedValue));
        m_sensitiveItemsTable->setItem(
            i, 3, new QTableWidgetItem(rows[i].destination));
    }
}

void DemoModePane::setExportPreviewText(const QString& text) {
    m_exportPreview->setText(text);
}

}  // namespace aura::gui
