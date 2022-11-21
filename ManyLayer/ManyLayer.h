#pragma once

#include "ManyLayerInterface.h"
#include "ManyLayerImplementation.h"

// Original ImageLayer by Seunghyun Min (https://github.com/MinSeungHyun)
// Initial refactoring by Donghyun Lee (https://github.com/ldhhello)
// Text renderer by Kangmin Kim (https://github.com/H2Owater425)

#ifndef MANY_LAYER_H_INCLUDED
#define MANY_LAYER_H_INCLUDED

static const ManyLayer DEFAULT_MANY_LAYER = { NULL, 0, NULL, 0, RGB(0, 0, 0), NULL, NULL, _initialize, _renderAll, NULL, _getBitmapHandle };

#endif
