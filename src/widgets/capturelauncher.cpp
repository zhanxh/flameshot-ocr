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
#include "src/utils/screengrabber.h"
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QMimeData>
#include <QDrag>
#include <QFormLayout>

// https://github.com/KDE/spectacle/blob/941c1a517be82bed25d1254ebd735c29b0d2951c/src/Gui/KSWidget.cpp
// https://github.com/KDE/spectacle/blob/941c1a517be82bed25d1254ebd735c29b0d2951c/src/Gui/KSMainWindow.cpp

CaptureLauncher::CaptureLauncher(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);


    QGridLayout *layout = new QGridLayout(this);
    m_imageLabel = new ImageLabel();
    bool ok;
    m_imageLabel->setScreenshot(ScreenGrabber().grabEntireDesktop(ok));
    if (!ok) {

    }
    m_imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(m_imageLabel, &ImageLabel::dragInitiated, this, &CaptureLauncher::startDrag);

    layout->addWidget(m_imageLabel, 0, 0);

    m_CaptureModeLabel = new QLabel(tr("<b>Capture Mode</b>"));

    m_captureType = new QComboBox();
    m_captureType->setMinimumWidth(240);
    m_captureType->insertItem(1, tr("Full Screen (All Monitors)")); // add variante end
    //m_captureType->insertItem(2, tr("Current Screen"), ImageGrabber::CurrentScreen);
    m_captureType->insertItem(5, tr("Rectangular Region"));

    m_delaySpinBox = new QSpinBox();
    m_delaySpinBox->setSingleStep(1.0);
    m_delaySpinBox->setMinimum(0.0);
    m_delaySpinBox->setMaximum(999.0);
    m_delaySpinBox->setSpecialValueText(tr("No Delay"));
    m_delaySpinBox->setMinimumWidth(160);
    // with QT 5.7 qOverload<int>(&QSpinBox::valueChanged),
    connect(m_delaySpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int val)
    {
        QString sufix = val == 1 ?tr(" second") : tr(" seconds");
        this->m_delaySpinBox->setSuffix(sufix);
    });

    m_launchButton = new QPushButton(tr("Take new screenshot"));
    m_launchButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(m_launchButton, &QPushButton::pressed,
            this, &CaptureLauncher::startCapture);

    QFormLayout *captureModeForm = new QFormLayout;
    captureModeForm->addRow(tr("Area:"), m_captureType);
    captureModeForm->addRow(tr("Delay:"), m_delaySpinBox);
    captureModeForm->setContentsMargins(24, 0, 0, 0);

    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addStretch(1);
    m_mainLayout->addWidget(m_CaptureModeLabel);
    m_mainLayout->addLayout(captureModeForm);
    m_mainLayout->addStretch(1);
    m_mainLayout->addWidget(m_launchButton);
    m_mainLayout->addStretch(1);
    m_mainLayout->setContentsMargins(10, 0, 0, 10);
    layout->addLayout(m_mainLayout, 0 ,1);
    layout->setColumnMinimumWidth(0, 320);
    layout->setColumnMinimumWidth(1, 320);

}

void CaptureLauncher::startCapture() {
    //hide();

    Controller::getInstance()->createVisualCapture();

    //show();
}

void CaptureLauncher::startDrag() {
    QDrag *dragHandler = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setImageData(m_imageLabel->pixmap());
    dragHandler->setMimeData(mimeData);

    dragHandler->setPixmap(m_imageLabel->pixmap()
                           ->scaled(256, 256, Qt::KeepAspectRatioByExpanding,
                                   Qt::SmoothTransformation));
    dragHandler->exec();
}
