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

#include "bullettool.h"
#include "bulletconfig.h"
#include "src/utils/confighandler.h"
#include "src/utils/colorutils.h"
#include <QPainter>

namespace {
#define PADDING_VALUE 20
}

unsigned int BulletTool::m_global_number = 0;

BulletTool::BulletTool(QObject *parent) : AbstractTwoPointTool(parent) {
}

QIcon BulletTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "num-bullet.svg");
}
QString BulletTool::name() const {
    return tr("Numbered Bullet");
}

QString BulletTool::nameID() {
    return QLatin1String("");
}

QString BulletTool::description() const {
    return tr("Set the Numbered Bullet as the paint tool");
}

CaptureTool* BulletTool::copy(QObject *parent) {
    return new BulletTool(parent);
}

void BulletTool::process(QPainter &painter, const QPixmap &pixmap, bool recordUndo) {
    if (recordUndo) {
        updateBackup(pixmap);
    }
    painter.setPen(QPen(m_color));
    painter.setBrush(QBrush(m_color));
    const int circlePadding = m_thickness;
    // TODO should check the content fits
    QRect circleRect = QRect(m_points.first, m_points.first + QPoint(circlePadding, circlePadding));
    painter.drawEllipse(circleRect);
    painter.setPen(QPen(m_textColor, m_thickness));
    QString str_number = numberToString(m_number);
    painter.drawText(circleRect, str_number);
}

void BulletTool::paintMousePreview(QPainter &painter, const CaptureContext &context) {
    painter.setPen(QPen(context.color, PADDING_VALUE + context.thickness));
    painter.drawLine(context.mousePos, context.mousePos);
}

QWidget* BulletTool::configurationWidget() {
    m_confW = new BulletConfig;
    return m_confW;
}

void BulletTool::undo(QPixmap &pixmap) {
    AbstractTwoPointTool::undo(pixmap);
    m_global_number--;
}

void BulletTool::drawStart(const CaptureContext &context) {
    m_color = context.color;
    m_thickness = context.thickness + PADDING_VALUE;
    m_points.first = context.mousePos;
    m_points.second = context.mousePos;
}

void BulletTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
}

void BulletTool::colorChanged(const QColor &c) {
    m_color = c;
    m_textColor = ColorUtils::colorIsDark(c) ? QColor(Qt::white) : QColor(Qt::black);
}

void BulletTool::updateMode(BulletMode mode) {
    m_mode = mode;
}

void BulletTool::updateNumber(const uint number) {
    m_global_number = number;
}

void BulletTool::increase_number() {
    m_global_number++;
    m_number = m_global_number;
}

QString BulletTool::numberToString(const uint number) const {
    QString res;
    switch (m_mode) {
    case BulletMode::NUMBER:
        res = QString::number(number);
        break;
    case BulletMode::ALPHABET:
        res = numberToAplhabet(number);
        break;
    case BulletMode::ROMAN:
        res = numberToRoman(number);
        break;
    }
    return res;
}

QString BulletTool::numberToAplhabet(const uint number) const {
    QString res;
    uint temp = number;
    uint decreaseValue = 'z' - 'a';
    while (temp > 0) {
        QString c('a' + (temp % decreaseValue));
        res = c + res;
        temp /= decreaseValue;
    }
    return res;
}

QString BulletTool::numberToRoman(const uint number) const {
    QString res;
    QString M[] = {"","M","MM","MMM","MMMM","MMMMM","MMMMMM","MMMMMMM","MMMMMMMM","MMMMMMMMM"};
    QString C[] = {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
    QString X[] = {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
    QString I[] = {"","I","II","III","IV","V","VI","VII","VIII","IX"};
    res = M[number/1000]+C[(number%1000)/100]+X[(number%100)/10]+I[(number%10)];
    return res;
}
