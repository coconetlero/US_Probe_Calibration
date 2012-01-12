#ifndef QUATERNIONS_H
#define QUATERNIONS_H

#endif // QUATERNIONS_H

#include <math.h>

class Quaternions
{
public:

  float trans[4][4];

  static Quaternions * New()
  {
    return new Quaternions;
  }

  void TransMatrix(float q[4], float translations[3])
  {

    float magnitud = sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
    q[0] /= magnitud;
    q[1] /= magnitud;
    q[2] /= magnitud;
    q[3] /= magnitud;

    trans[0][0] = 1 - 2 * (q[2] * q[2] + q[3] * q[3]);
    trans[0][1] = 2 * (q[1] * q[2] - q[0] * q[3]);
    trans[0][2] = 2 * (q[0] * q[2] + q[1] * q[3]);
    trans[0][3] = translations[0];

    trans[1][1] = 1 - 2 * (q[1] * q[1] + q[3] * q[3]);
    trans[1][0] = 2 * (q[1] * q[2] + q[0] * q[3]);
    trans[1][2] = 2 * (q[2] * q[3] - q[0] * q[1]);
    trans[1][3] = translations[1];

    trans[2][2] = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);
    trans[2][1] = 2 * (q[0] * q[1] + q[2] * q[3]);
    trans[2][0] = 2 * (q[1] * q[3] - q[0] * q[2]);
    trans[2][3] = translations[2];

    trans[3][0] = 0.0;
    trans[3][1] = 0.0;
    trans[3][2] = 0.0;
    trans[3][3] = 1.0;

  }
};
