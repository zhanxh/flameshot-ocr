// Copyright(c) 2017-2018 Alejandro Sirgo Rica & Contributors
//
// This file is part of Flameshot.
//
//     Flameshot is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     Flameshot is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with Flameshot.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "src/tools/abstracttwopointtool.h"
#include <QPointer>

class BulletConfig;

enum class BulletMode {
    NUMBER,
    ALPHABET,
    ROMAN,
};

class BulletTool : public AbstractTwoPointTool {
    Q_OBJECT
public:
    explicit BulletTool(QObject *parent = nullptr);

    QIcon icon(const QColor &background, bool inEditor) const override;
    QString name() const override;
    static QString nameID();
    QString description() const override;

    CaptureTool* copy(QObject *parent = nullptr) override;
    void process(
            QPainter &painter, const QPixmap &pixmap, bool recordUndo = false) override;
    void paintMousePreview(QPainter &painter, const CaptureContext &context) override;

    QWidget* configurationWidget() override;
    void undo(QPixmap &pixmap) override;

public slots:
    void drawStart(const CaptureContext &context) override;
    void pressed(const CaptureContext &context) override;
    void colorChanged(const QColor &c) override;

private slots:
    void updateMode(BulletMode mode);
    void updateNumber(const uint number);

private:
    static uint m_global_number;
    uint m_number;
    BulletMode m_mode;
    QColor m_textColor;
    QPointer<BulletConfig> m_confW;

    void increase_number();
    QString numberToString(const uint number) const;
    QString numberToRoman(const uint number) const;
    QString numberToAplhabet(const uint number) const;
};
