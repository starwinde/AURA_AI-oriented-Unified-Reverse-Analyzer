// src/gui/demo_mode_pane.h — graduation demo flow pane.
//
// A viewer-facing widget that shows the Analyze -> Detect -> Mask -> Export
// story without wiring into MainWindow yet. Task 3 owns integration.

#pragma once

#include <QString>
#include <QVector>
#include <QWidget>

class QSize;
class QLabel;
class QTableWidget;

namespace aura::gui {

struct DemoSensitiveItemRow {
    QString category;
    QString originalValue;
    QString maskedValue;
    QString destination;
};

class DemoModePane final : public QWidget {
    Q_OBJECT

public:
    explicit DemoModePane(QWidget* parent = nullptr);

    void setBinaryName(const QString& name);
    void setEngineName(const QString& name);
    void setSummary(int extractedStrings, int protectedStrings, int exportRows);
    void setSensitiveItems(const QVector<DemoSensitiveItemRow>& rows);
    void setExportPreviewText(const QString& text);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    QWidget* makeStageCard(const QString& objectName,
                           const QString& title,
                           const QString& body);

    QLabel*       m_claimLabel = nullptr;
    QLabel*       m_binaryLabel = nullptr;
    QLabel*       m_engineLabel = nullptr;
    QLabel*       m_summaryLabel = nullptr;
    QTableWidget* m_sensitiveItemsTable = nullptr;
    QLabel*       m_exportPreview = nullptr;
};

}  // namespace aura::gui
