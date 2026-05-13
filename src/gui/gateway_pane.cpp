// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "gateway_pane.h"

#include <QHeaderView>
#include <QLabel>
#include <QPlainTextEdit>
#include <QStringList>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

namespace aura::gui {
namespace {

QString checkLabel(const QString& id) {
    if (id == QStringLiteral("protection_enabled")) {
        return QStringLiteral("보호 기능 활성화");
    }
    if (id == QStringLiteral("safety_scan_executed")) {
        return QStringLiteral("안전 스캔 실행");
    }
    if (id == QStringLiteral("safety_profile_applied")) {
        return QStringLiteral("안전 프로필 적용");
    }
    if (id == QStringLiteral("rule_packs_loaded")) {
        return QStringLiteral("Rule Pack 로드");
    }
    if (id == QStringLiteral("active_rule_count")) {
        return QStringLiteral("활성 규칙 존재");
    }
    if (id == QStringLiteral("masking_cache_current")) {
        return QStringLiteral("마스킹 결과 최신");
    }
    if (id == QStringLiteral("protected_prompt_generated")) {
        return QStringLiteral("보호 프롬프트 생성");
    }
    if (id == QStringLiteral("original_values_not_included")) {
        return QStringLiteral("원본값 미포함");
    }
    if (id == QStringLiteral("protected_items_present")) {
        return QStringLiteral("보호 항목 존재");
    }
    return id;
}

}  // namespace

GatewayPane::GatewayPane(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);

    m_statusLabel = new QLabel(QStringLiteral("LLM 전송 상태: 대기"), this);
    m_statusLabel->setObjectName(QStringLiteral("gatewayStatusLabel"));
    layout->addWidget(m_statusLabel);

    m_summaryLabel =
        new QLabel(QStringLiteral("탐지 0개 / 마스킹 0개 / 차단 0개"), this);
    m_summaryLabel->setObjectName(QStringLiteral("gatewaySummaryLabel"));
    layout->addWidget(m_summaryLabel);

    m_prompt = new QPlainTextEdit(this);
    m_prompt->setObjectName(QStringLiteral("gatewayProtectedPrompt"));
    m_prompt->setReadOnly(true);
    m_prompt->setMinimumHeight(180);
    layout->addWidget(m_prompt, 1);

    m_verification = new QTreeWidget(this);
    m_verification->setObjectName(QStringLiteral("gatewayVerificationTable"));
    m_verification->setColumnCount(3);
    m_verification->setHeaderLabels(
        QStringList{QStringLiteral("검증"), QStringLiteral("결과"),
                    QStringLiteral("세부 정보")});
    m_verification->setRootIsDecorated(false);
    m_verification->setUniformRowHeights(true);
    m_verification->header()->setStretchLastSection(true);
    layout->addWidget(m_verification, 1);

    m_audit = new QTreeWidget(this);
    m_audit->setObjectName(QStringLiteral("gatewayAuditTable"));
    m_audit->setColumnCount(4);
    m_audit->setHeaderLabels(
        QStringList{QStringLiteral("Action"), QStringLiteral("Category"),
                    QStringLiteral("Preview"), QStringLiteral("Reason")});
    m_audit->setRootIsDecorated(false);
    m_audit->setUniformRowHeights(true);
    m_audit->header()->setStretchLastSection(true);
    layout->addWidget(m_audit, 1);
}

void GatewayPane::setSnapshot(
    const aura::gateway::GatewaySnapshot& snapshot) {
    switch (snapshot.verification.status) {
        case aura::gateway::GatewayReadinessStatus::Pass:
            m_statusLabel->setText(QStringLiteral("LLM 전송 상태: PASS"));
            break;
        case aura::gateway::GatewayReadinessStatus::Warning:
            m_statusLabel->setText(
                QStringLiteral("최종 전송 판정: WARNING"));
            break;
        case aura::gateway::GatewayReadinessStatus::NotReady:
            m_statusLabel->setText(
                QStringLiteral("최종 전송 판정: NOT_READY"));
            break;
        case aura::gateway::GatewayReadinessStatus::Disabled:
            m_statusLabel->setText(
                QStringLiteral("최종 전송 판정: DISABLED"));
            break;
        case aura::gateway::GatewayReadinessStatus::Fail:
            m_statusLabel->setText(QStringLiteral("최종 전송 판정: FAIL"));
            break;
    }

    int masked = 0;
    int blocked = 0;
    for (const auto& item : snapshot.protected_items) {
        if (item.action == aura::gateway::GatewayPolicyAction::Mask) {
            ++masked;
        } else if (item.action == aura::gateway::GatewayPolicyAction::Block) {
            ++blocked;
        }
    }
    m_summaryLabel->setText(
        QStringLiteral("탐지 %1개 / 마스킹 %2개 / 차단 %3개")
            .arg(static_cast<int>(snapshot.protected_items.size()))
            .arg(masked)
            .arg(blocked));

    m_prompt->setPlainText(QString::fromStdString(snapshot.prompt.body));

    m_verification->clear();
    for (const auto& check : snapshot.verification.checks) {
        const QString rawId = QString::fromStdString(check.name);
        auto* row = new QTreeWidgetItem();
        row->setText(0, checkLabel(rawId));
        row->setToolTip(0, rawId);
        row->setText(
            1, QString::fromLatin1(
                   aura::gateway::gatewayCheckStatusToText(check.status)));
        row->setText(2, QString::fromStdString(check.detail));
        m_verification->addTopLevelItem(row);
    }

    m_audit->clear();
    for (const auto& event : snapshot.audit_events) {
        auto* row = new QTreeWidgetItem();
        row->setText(0, QString::fromStdString(event.action));
        row->setText(1, QString::fromStdString(event.category));
        row->setText(2, QString::fromStdString(event.safe_preview));
        row->setText(3, QString::fromStdString(event.reason));
        m_audit->addTopLevelItem(row);
    }
}

}  // namespace aura::gui
