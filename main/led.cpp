#include "led.h"

// Define the pins for the NeoPixel strips
const int LED_PINS[7] = {2, 3, 4, 5, 6, 7, 8};
const int LED_COUNT = 100;


// Define the array of Adafruit_NeoPixel objects
Adafruit_NeoPixel strips[7] = {
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[0], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[1], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[2], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[3], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[4], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[5], NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(LED_COUNT, LED_PINS[6], NEO_GRB + NEO_KHZ800)
};

void LEDSystem::initLEDs(){

  int rows = 7;
  float distance = 16.0;
  generate_grid(rows, distance);
  Serial.println("Geometry Generated");
  
  //populate_map(points, pin_dict);

}

// Set the geometry of the LED system
void LEDSystem::setGeometry(int n_rows, int n_cols, int n_pixels_per_substrip,
                           float hex_size, float led_distance,
                           int between_substrip_led_offset,
                           int first_led_offset, float strip_offset_from_ground, float strip_offset_from_ceiling)
{
    // Validate input
    if (n_rows <= 0 || n_cols <= 0 || n_pixels_per_substrip <= 0 || hex_size <= 0 || led_distance <= 0) {
        //throw std::invalid_argument("Geometry parameters must be positive.");
    }

    // Store geometry parameters
    this->n_rows = n_rows;
    this->n_cols = n_cols;
    this->n_pixels_per_substrip = n_pixels_per_substrip;
    this->between_substrip_offset = between_substrip_led_offset;
   // this->strip_offset_from_ground = strip_offset_from_ground;
   // this->strip_offset_from_ceiling = strip_offset_from_ceiling;

    // Store distances
    this->hex_size = hex_size;             // Distance between nodes in the hexagonal grid
    //this->edge_size = hex_size / 1.73205f; // Edge size of the hexagon
    this->led_distance = led_distance;     // Distance between LEDs on a strip
    this->first_led_offset = first_led_offset;

    // Calculate offsets for the hexagonal grid
}
/*
void LEDSystem::drawPixel(coordinate coor, float radius, int r, int g, int b) {
    int x_min = static_cast<int>(std::floor(coor.x - radius));
    int x_max = static_cast<int>(std::ceil(coor.x + radius));
    int y_min = static_cast<int>(std::floor(coor.y - radius));
    int y_max = static_cast<int>(std::ceil(coor.y + radius));
    int z_min = static_cast<int>(std::floor(coor.z - radius));
    int z_max = static_cast<int>(std::ceil(coor.z + radius));

    for (int x = x_min; x <= x_max; ++x) {
        for (int y = y_min; y <= y_max; ++y) {
            for (int z = z_min; z <= z_max; ++z) {
                coordinate current = {x, y, z};
                if (coordinate_pixel_map.find(current) != coordinate_pixel_map.end()) {
                    led_PIN_pixel led_pixel = coordinate_pixel_map[current];
                    strips[led_pixel.PIN]->setPixelColor(led_pixel.pixel_index, r, g, b);
                }
            }
        }
    }
}
*/
void LEDSystem::show() {
    for (int i = 0; i < 7; i++) {
    strips[i].show();
  }
}
void LEDSystem::clear(){
    for (int i = 0; i < 7; i++) {
    for (int j = 0; j < LED_COUNT; j++) {
      strips[i].setPixelColor(j, strips[i].Color(0, 0, 0));
    }
    strips[i].show();
  }
}

// Build the LED system
void LEDSystem::build() {
    buildCoordinatePixelMap();
    // in case something here
}


// Build the coordinate-to-pixel map
void LEDSystem::buildCoordinatePixelMap() {
    //coordinate_pixel_map.clear();
    for (int col = 0; col < n_cols; ++col) {
        buildColumnCoordinatePixelMap(col);
    }

}

void LEDSystem::buildColumnCoordinatePixelMap(int col) {
  /*
    int led_start = first_led_offset;
    bool is_long_column = (col % 2 == 0); // Determine if the column is a long column
    float x_start = is_long_column 
                    ? edge_size + 3 * col / 2 * edge_size 
                    : 2.5 * edge_size + (col / 2) * 3 * edge_size;
    float y_start = is_long_column ? hex_size / 2 : hex_size;
    bool from_ground = true;

    int max_rows = is_long_column ? n_rows : n_rows - 1;

    for (int row = 0; row < max_rows; ++row) {
        float x = is_long_column ? x_start : x_start + col * edge_size * 2;
        float y = y_start + row * hex_size;
        float z_start = strip_offset_from_ground;

        for (int i = 0; i < n_pixels_per_substrip; ++i) {
            float z = z_start + i * led_distance;
            int x_floor = static_cast<int>(std::floor(x));
            int y_floor = static_cast<int>(std::floor(y));
            int z_floor = static_cast<int>(std::floor(z));

            int pixel_index = from_ground ? led_start + i : (led_start + n_pixels_per_substrip - 1 - i);
            led_PIN_pixel led_pixel = {col, pixel_index};
            coordinate coord = {x_floor, y_floor, z_floor};
            coordinate_pixel_map[coord] = led_pixel;
        }

        led_start = led_start + n_pixels_per_substrip + between_substrip_offset;
        from_ground = !from_ground; // Toggle if needed per row
    }
    */
}
void LEDSystem::generate_grid(int rows, float distance) {
    int cnt=0;
    for (int row = 0; row < rows; row++) {
        int num_points = (row % 2 == 0) ? 7 : 6;
        bool top = (row % 2 == 0);
        int ledcnt=99;
        for (int col = 0; col < num_points; col++) {
            float x = col * distance * sqrt(3) / 2;
            float y = row * distance * sqrt(3) / 2;
            if (row % 2 == 1) {
                x += distance * sqrt(3) / 4;
            }
            x += 8;
            y += 8;
            for(int lay=0; lay<10; lay++){
              int ledid = top ? (ledcnt - 9 + lay) : (ledcnt - lay);
              float z=lay*10+5;
              coordinate pnt = {x, y, z};
              int strip_id = get_pin_id(int(y));
              pixel_ID pxl={strip_id,ledid};
              points[cnt]=pnt;
              pins[cnt]=pxl;
              cnt++;
              /*
              Serial.print(pnt.x);
              Serial.print(",");
              Serial.print(pnt.y);
              Serial.print(",");
              Serial.print(pnt.z);
              Serial.print(",");
              Serial.print(pxl.strip);
              Serial.print(",");
              Serial.println(pxl.pixel);
              Serial.println("");
              */
            }
            top = !top;
            ledcnt -= 13;
        }
    }
}
int LEDSystem::get_pin_id(int y) {
    const int keys[] = {8, 21, 35, 49, 63, 77, 91}; //check these!!!!
    const int values[] = {2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 7; i++) {
        if (keys[i] == y) {
            return values[i];
        }
    }
    return -1; // Return -1 if the key is not found
}

/*
void LEDSystem::populate_map(std::vector<coordinate> points, std::map<float, int> pin_dict) {
    
    
    for (auto& [index, point] : points) {
      int cols = points.size() /10; 
      bool top = false;
      if(cols == 7) top=true;
      for(int i=0; i<cols; ++i){
        for(int j=0; j<10; j++){
          int ledid = top ? (ledcnt - 9 + j) : (ledcnt - j);
          pixel_ID px = {pin_dict[point.y],ledid};
          coordinate_pixel_map[point] = px;
        }
        top = !top;
        ledcnt -= 13;
      }
    }





    std::map<float, std::map<int, coordinate>> points_dict;
    for (auto point = points.begin(); point != points.end(); ++point){
        float y_value = round(point->second.y);
        if (points_dict.find(y_value) == points_dict.end()) {
            points_dict[y_value] = std::map<int, coordinate>();
        }
        int point_id = points_dict[y_value].size();
        points_dict[y_value][point_id] = point->second;
    }

    int ledid = 99;
    bool top = false;
    for (auto& [y_value, point_map] : points_dict) {
        int cols = point_map.size() / 10;
        if (cols == 7) top = true;
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < 10; j++) {
                int oldid = 10 * i + j;
                coordinate coord = point_map[oldid];
                int newid = top ? (ledid - 9 + j) : (ledid - j);
                pixel_ID newpx = {pin_dict[y_value],newid};
                coordinate_pixel_map[coord] = newpx;
            }
            top = !top;
            ledid -= 13;
        }
    }
  }
    */

void LEDSystem::printMap(){
  // Print the map for verification
  Serial.println("print map");
  for (int i=0; i<460; ++i) {
        Serial.print("Coordinate: ");
        Serial.print(points[i].x);
        Serial.print(", ");
        Serial.print(points[i].y);
        Serial.print(", ");
        Serial.print(points[i].z);
        Serial.print(" -> Pixel ID: ");
        Serial.print(pins[i].strip);
        Serial.print(", ");
        Serial.println(pins[i].pixel);
    }
}
void LEDSystem::setPixel(int pixel, int r, int g, int b){
  strips[0].setPixelColor(pixel, strips[0].Color(r,g,b));
}

