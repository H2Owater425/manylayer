# ManyLayer
[ImageLayer](https://github.com/MinSeungHyun/CodeTheCompany) 개조판


## 감사한 분들
[Seunghyun Min](https://github.com/MinSeungHyun) (ImageLayer를 만들어주셨습니다)
<br/>
[Donghyun Lee](https://github.com/ldhhello) (코드를 효율적으로 개선해주셨습니다)

## 사용법

기본적인 사용법은 ImageLayer와 비슷하지만, 텍스트도 출력할 수 있기에 이름만 바꿔봤습니다

### 초기화 코드
```c
#include <stdbool.h>
#include "ManyLayer/ManyLayer.h"
```
콘솔 크기는 진행중인 프로젝트에 맞게 [ManyLayerImplementation.h](https://github.com/H2Owater425/manylayer/blob/main/ManyLayer/ManyLayerImplementation.h)의 아래 값을 바꿔주세요
```c
#define CONSOLE_WIDTH 160
#define CONSOLE_HEIGHT 45
```

### 이미지 출력 코드
```c
int main(void) {
	ManyLayer manyLayer = DEFAULT_MANY_LAYER;

	manyLayer.initialize(&manyLayer);

	manyLayer.images = (Image[]){
		{ manyLayer.getBitmapHandle(L"images/block1.bmp"), 0, 0, 4, false },
		{ manyLayer.getBitmapHandle(L"images/block2.bmp"), 0, 300, 4, false },
		{ manyLayer.getBitmapHandle(L"images/block3.bmp"), 0, 600, 4, false },
	};

	manyLayer.imageCount = 3;

	manyLayer.renderAll(&manyLayer);

	return 0;
}
```

`manyLayer.getBitmapHandle(L"이미지 경로")`은 `HBITMAP`를 반환하고, `(HBITMAP)LoadImageW(NULL, L"이미지 경로", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)`와 같은 기능을 합니다
<br/>
이미지를 추가하시려면 `manyLayer.images` 배열에 `{ HBITMAP, x 좌표, y 좌표, 배율, 출력 안 함 여부 }`를 추가해주시고, 배열의 길이를 위 코드와 같이 추가해주시면 됩니다

#### 출력 결과
![image](https://user-images.githubusercontent.com/50160366/202993109-0f7c9809-d0c2-48fa-aacb-a11487ce2cd8.png)

### 텍스트 출력
```c
int main(void) {
	ManyLayer manyLayer = DEFAULT_MANY_LAYER;

	manyLayer.initialize(&manyLayer);

	manyLayer.texts = (Text[]){
		{ L"테스트1", 300, 0, 48, 64, 600, L"굴림", RGB(255, 255, 255), false },
		{ L"테스트2", 300, 300, 48, 64, 600, L"굴림", RGB(255, 255, 255), false },
		{ L"테스트3", 300, 600, 48, 64, 600, L"굴림", RGB(255, 255, 255), false },
	};

	manyLayer.textCount = 3;

	manyLayer.renderAll(&manyLayer);

	return 0;
}
```

텍스트를 추가하시려면 `manyLayer.texts` 배열에 `{ 내용, x 좌표, y 좌표, 가로 길이, 세로 길이, 굵기, 색깔, 출력 안 함 여부 }`를 추가해주시고, 배열의 길이를 위 코드와 같이 추가해주시면 됩니다

#### 출력 결과
![image](https://user-images.githubusercontent.com/50160366/202993897-25f7f68d-37fe-4f06-a8c6-99d321f01aca.png)

### 텍스트와 이미지 동시 출력
```c
int main(void) {
	ManyLayer manyLayer = DEFAULT_MANY_LAYER;

	manyLayer.initialize(&manyLayer);

	manyLayer.images = (Image[]){
		{ manyLayer.getBitmapHandle(L"images/block1.bmp"), 0, 0, 4, false },
		{ manyLayer.getBitmapHandle(L"images/block2.bmp"), 0, 300, 4, false },
		{ manyLayer.getBitmapHandle(L"images/block3.bmp"), 0, 600, 4, false },
	};

	manyLayer.imageCount = 3;

	manyLayer.texts = (Text[]){
		{ L"테스트1", 300, 0, 48, 64, 600, L"굴림", RGB(255, 255, 255), false },
		{ L"테스트2", 300, 300, 48, 64, 600, L"굴림", RGB(255, 255, 255), false },
		{ L"테스트3", 300, 600, 48, 64, 600, L"굴림", RGB(255, 255, 255), false },
	};

	manyLayer.textCount = 3;

	manyLayer.renderAll(&manyLayer);

	return 0;
}
```

#### 출력 결과
![image](https://user-images.githubusercontent.com/50160366/202994055-69e0954c-1a07-4720-a75a-55deb7300219.png)

텍스트는 언제나 이미지 위에 출력됩니다
