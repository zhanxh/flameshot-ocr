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

#include "capturelauncher.h"
#include "src/core/controller.h"
#include "src/widgets/imagelabel.h"
#include "src/widgets/notificationwidget.h"
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>

// https://github.com/KDE/spectacle/blob/941c1a517be82bed25d1254ebd735c29b0d2951c/src/Gui/KSWidget.cpp
// https://github.com/KDE/spectacle/blob/941c1a517be82bed25d1254ebd735c29b0d2951c/src/Gui/KSMainWindow.cpp

CaptureLauncher::CaptureLauncher(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    mCaptureModeLabel = new QLabel(i18n("<b>Capture Mode</b>"), this);

    m_mainLayout = new QVBoxLayout(this);

    m_launchButton = new QPushButton(this);
    m_launchButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(m_launchButton, &QPushButton::pressed,
            this, &CaptureLauncher::prepareCapture);

    m_captureType = new QComboBox();
    m_captureType->setMinimumWidth(240);
    m_captureType->insertItem(1, tr("Full Screen (All Monitors)")); // add variante end
    //m_captureType->insertItem(2, tr("Current Screen"), ImageGrabber::CurrentScreen);
    m_captureType->insertItem(5, tr("Rectangular Region"));

    m_delaySpinBox = new QSpinBox();
    m_delaySpinBox->setDecimals(1);
    m_delaySpinBox->setSingleStep(1.0);
    m_delaySpinBox->setMinimum(0.0);
    m_delaySpinBox->setMaximum(999.9);
    m_delaySpinBox->setSpecialValueText(tr("No Delay"));
    m_delaySpinBox->setMinimumWidth(160);
}

void CaptureLauncher::prepareCapture() {
    hide(); // TODO
}

void CaptureLauncher::startCapture() {
    Controller::getInstance()->createVisualCapture();

    //show();
}
