
## flameshot-ocr

在[flameshot](https://github.com/flameshot-org/flameshot)基础上增加一个OCR功能，截图取文字，方便上网课作笔记，提高学习效率。

## 编译

```shell
mkdir build
cd build
cmake ../
make
```

#### Windows 建议

```
QT5
Visual Studio 2017
vcpkg：openssl curl jsoncpp
msys: ccache cmake 
```

### 依赖

#### 编译

- Qt >= 5.9
  - Development tools
- GCC >= 7.4
- CMake >= 3.13

#### 运行

- Qt
  - SVG

#### OCR

- openssl
- curl
- jsoncpp

## OCR

目前仅支持百度ocr，白漂500次/月

#### 配制ocr.json 

```json
{
        "baidu":{
                "app_id":"你的app_id",
                "api_key":"你的app_key",
                "secret_key":"你的secret_key"
        }
}
```

***注：位置同执行程序目录***

参考[百度OCR](https://cloud.baidu.com/doc/OCR/s/Kk3h7y7vq)



