/*

Copyright MUS 2020

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/


#include <lv2plugin.hpp>
#include <math.h>

using namespace LV2;

class Musatan : public Plugin<Musatan> {
public:

  Musatan(double rate)
    : Plugin<Musatan>(9), pi(3.1415926535897932384626433832795), piovertwo(2/pi) {

  }

  void run(uint32_t nframes) {

    float amp = *p(4);
    float drive = *p(5);
    float d_ratio = *p(6);
    float dry = *p(7);
    float wet = *p(8);

    amp = amp < 0 ? 0 : amp;
    amp = amp > 1 ? 1 : amp;

    drive = drive < 0 ? 0 : drive;
    drive = drive > 100 ? 100 : drive;

    d_ratio = d_ratio < 0 ? 0 : d_ratio;
    d_ratio = d_ratio > 1 ? 1 : d_ratio;

    dry = dry < 0 ? 0 : dry;
    dry = dry > 1 ? 1 : dry;

    wet = wet < 0 ? 0 : wet;
    wet = wet > 1 ? 1 : wet;

    float totdrive = drive * d_ratio;

    for (uint32_t i = 0; i < nframes; ++i) {

      float left = p(0)[i];
      float right = p(1)[i];

      float l_dist = piovertwo * atan(left * totdrive);
      float r_dist = piovertwo * atan(right * totdrive);

      float l_sig = (left * dry) + (l_dist * wet);
      float r_sig = (right * dry) + (r_dist * wet);

      p(2)[i] = l_sig * amp;
      p(3)[i] = r_sig * amp;

    }

  }

protected:

  double pi;
  double piovertwo;

};

static int _ = Musatan::register_class("http://musens.pluggar/lv2/lv2pftci/musatan");
