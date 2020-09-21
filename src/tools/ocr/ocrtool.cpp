// Copyright(c) 2017-2019 Alejandro Sirgo Rica & Contributors
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

#include "ocrtool.h"
#include "src/utils/screenshotsaver.h"
#include <QPainter>
#include <qbuffer.h>

aip::Ocr* OcrTool::baiduOcr = nullptr;

OcrTool::OcrTool(QObject* parent)
  : AbstractActionTool(parent)
{
    CreateOcr();
}

bool
OcrTool::closeOnButtonPressed() const
{
  return true;
}

QIcon
OcrTool::icon(const QColor& background, bool inEditor) const
{
  Q_UNUSED(inEditor);
  return QIcon(iconPath(background) + "content-ocr.svg");
}
QString
OcrTool::name() const
{
  return tr("Ocr");
}

ToolType
OcrTool::nameID() const
{
  return ToolType::OCR;
}

QString
OcrTool::description() const
{
  return tr("Ocr the selection into the clipboard");
}

CaptureTool*
OcrTool::copy(QObject* parent)
{
  return new OcrTool(parent);
}

void
OcrTool::pressed(const CaptureContext& context)
{
  emit requestAction(REQ_CAPTURE_DONE_OK);
  QPixmap bmp = context.selectedScreenshotArea();
  QByteArray ba = QByteArray();
  QBuffer buffer(&ba);
  buffer.open(QIODevice::WriteOnly);
  bmp.save(&buffer, "bmp", 0);
  //std::cout<<"QByteArray Len" << ba.length() << "\r\n BufferSize: " <<buffer.size() << std::endl;
  //QString data = QString(ba);
  DoOcr(ba);
  
//   if (context.savePath.isEmpty()) {
//     emit requestAction(REQ_HIDE_GUI);
//     bool ok =
//       ScreenshotSaver().saveToFilesystemGUI(context.selectedScreenshotArea());
//     if (ok) {
//       emit requestAction(REQ_CAPTURE_DONE_OK);
//     }
//   } else {
//     bool ok = ScreenshotSaver().saveToFilesystem(
//       context.selectedScreenshotArea(), context.savePath, "");
//     if (ok) {
//       emit requestAction(REQ_CAPTURE_DONE_OK);
//     }
//   }
}

void OcrTool::CreateOcr()
{
    if(nullptr == baiduOcr){
        std::ifstream ifs("ocr.json");
        Json::Value root;
        Json::CharReaderBuilder builder;
        builder["collectComments"] = true;
        JSONCPP_STRING errs;
        if (!parseFromStream(builder, ifs, &root, &errs)) {
            std::cout << errs << std::endl;
            return;
        }
        std::cout << root << std::endl;
        Json::Value baiduCfg = root["baidu"];
        std::string app_id = baiduCfg["app_id"].asString();
        std::string api_key = baiduCfg["api_key"].asString();
        std::string secret_key = baiduCfg["secret_key"].asString();

        baiduOcr = new aip::Ocr(app_id,api_key,secret_key);
    }
}
void 
OcrTool::DoOcr(const QByteArray data)
{
     std::string str(data, data.length());
     Json::Value  result = baiduOcr->general_basic(str, aip::null);
     Json::String  rst;// = result.asString();
     Json::Value words = result["words_result"];
     for ( int index = 0; index < words.size(); ++index )
     {
         Json::Value word = words[index];
         rst.append(word["words"].asString());
         rst.append("\r\n");
     }
     ScreenshotSaver().saveToClipboard(rst.c_str());
}
