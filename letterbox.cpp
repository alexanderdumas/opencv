typedef struct _SIMPLE_LETTER_BOX {
  int in_width = 0, in_height = 0;
  int target_width = 0, target_height = 0;
  float scale = 0.0;
  int x = 0, y = 0;
  int w = 0, h = 0;
  int c_w = 0, c_h = 0;
  int left = 0, right = 0, top = 0, bottom = 0;
  int crop_width = 0, crop_height = 0;
  int crop_x = 0, crop_y = 0;
  int channel = 3;
}SIMPLE_LETTER_BO;

void compute_simple_letter_box(SIMPLE_LETTER_BO *lb) {
  float r_w = lb->target_width / (lb->in_width * 1.0);
  float r_h = lb->target_height / (lb->in_height * 1.0);
  if (r_h > r_w) {
    lb->w = lb->target_width;
    lb->h = r_w * lb->in_height;
    lb->x = 0;
    lb->y = (lb->target_height - lb->h) / 2;
  } else {
    lb->w = r_h * lb->in_width;
    lb->h = lb->target_height;
    lb->x = (lb->target_width - lb->w) / 2;
    lb->y = 0;
  }
  lb->scale = std::min(r_w, r_h);
  int pad_width = lb->target_width - lb->w;
  //yolov6 need stride=32
  pad_width = pad_width % 32;
  int pad_height = lb->target_height - lb->h;
  pad_height = pad_height % 32;
  //left,right,top,bottom
  lb->left = pad_width / 2;
  lb->right = pad_width - lb->left;
  lb->top = pad_height / 2;
  lb->bottom = pad_height - lb->top;

  //correct w,h
  lb->c_w = lb->w + lb->left + lb->right;
  lb->c_h = lb->h + lb->top + lb->bottom;

  //width aligned
  lb->crop_width = lb->target_width + lb->left + lb->right;
  lb->crop_height = lb->target_height - lb->h - lb->top - lb->bottom;
  lb->channel = 3;
}