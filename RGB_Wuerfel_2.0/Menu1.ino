void fullRed() {
  const byte animationData[1][3][2] = {{{0xFF, 0xFF}, {0x00, 0x00}, {0x00, 0x00}}};
  const boolean layerSelection[1][4] = {{true, true, true, true}};

  DisplayStatic(animationData, layerSelection, 10, 1);
}

void fullGreen() {
  const byte animationData[1][3][2] = {{{0x00, 0x00}, {0xFF, 0xFF}, {0x00, 0x00}}};
  const boolean layerSelection[1][4] = {{true, true, true, true}};

  DisplayStatic(animationData, layerSelection, 10, 1);
}

void fullBlue() {
  const byte animationData[1][3][2] = {{{0x00, 0x00}, {0x00, 0x00}, {0xFF, 0xFF}}};
  const boolean layerSelection[1][4] = {{true, true, true, true}};

  DisplayStatic(animationData, layerSelection, 10, 1);
}

void fullYellow(){
  const byte animationData[1][3][2] = {{{0xFF, 0xFF}, {0xFF, 0xFF}, {0x00, 0x00}}};
  const boolean layerSelection[1][4] = {{true, true, true, true}};

  DisplayStatic(animationData, layerSelection, 10, 1);
}

void fullPurple() {
  const byte animationData[1][3][2] = {{{0xFF, 0xFF}, {0x00, 0x00}, {0xFF, 0xFF}}};
  const boolean layerSelection[1][4] = {{true, true, true, true}};

  DisplayStatic(animationData, layerSelection, 10, 1);
}

void fullLigthBlue() {
  const byte animationData[1][3][2] = {{{0x00, 0x00}, {0xFF, 0xFF}, {0xFF, 0xFF}}};
  const boolean layerSelection[1][4] = {{true, true, true, true}};

  DisplayStatic(animationData, layerSelection, 10, 1);
}

void fullWhite() {
  const byte animationData[1][3][2] = {{{0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}}};
  const boolean layerSelection[1][4] = {{true, true, true, true}};

  DisplayStatic(animationData, layerSelection, 10, 1);
}