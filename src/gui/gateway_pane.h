// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "aura/gateway/gateway_snapshot.h"

#include <QWidget>

class QLabel;
class QPlainTextEdit;
class QTreeWidget;

namespace aura::gui {

class GatewayPane final : public QWidget {
    Q_OBJECT

public:
    explicit GatewayPane(QWidget* parent = nullptr);

    void setSnapshot(const aura::gateway::GatewaySnapshot& snapshot);

private:
    QLabel* m_statusLabel = nullptr;
    QLabel* m_summaryLabel = nullptr;
    QPlainTextEdit* m_prompt = nullptr;
    QTreeWidget* m_verification = nullptr;
    QTreeWidget* m_audit = nullptr;
};

}  // namespace aura::gui
