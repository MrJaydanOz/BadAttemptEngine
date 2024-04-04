#pragma once

/// <summary> The smallest reasonable value that is not zero. </summary>
const float EPSILON = 1E-35f;
/// <summary> The smallest reasonable value that is not zero. </summary>
const double EPSILON_D = 1E-314;
/// <summary> The smallest possible value that when added to one is not programmatically equal to one. </summary>
const float BIG_EPSILON = 1E-7f;
/// <summary> The smallest possible value that when added to one is not programmatically equal to one. </summary>
const double BIG_EPSILON_D = 1E-15;
/// <summary> An arbitrary small value. </summary>
const float VISIBLE_EPSILON = 1E-4f;
/// <summary> Equal to 1 + <seealso cref="BIG_EPSILON"/> </summary>
const float ONE_BIG_EPSILON = 1.0f + BIG_EPSILON;
/// <summary> Equal to 1 + <seealso cref="BIG_EPSILON_D"/> </summary>
const double ONE_BIG_EPSILON_D = 1.0 + BIG_EPSILON_D;
/// <summary> Equal to 1 + <seealso cref="VISIBLE_EPSILON"/> </summary>
const float ONE_VISIBLE_EPSILON = 1.0f + VISIBLE_EPSILON;

/// <summary> The ratio of the circumference of a circle relative to its diameter. </summary>
const float PI = 3.1415926535f;
/// <summary> The ratio of the circumference of a circle relative to its diameter. </summary>
const double PI_D = 3.14159265358979323846;
/// <summary> The ratio of the circumference of a circle relative to its radius. </summary>
const float TAU = PI * 2.0f;
/// <summary> The ratio of the circumference of a circle relative to its radius. </summary>
const double TAU_D = PI_D * 2.0;
/// <summary> The square root of 2. </summary>
const float SQRT_2 = 1.4142135623f;
/// <summary> The square root of 2. </summary>
const double SQRT_2_D = 1.41421356237309504880;
/// <summary> The reciprical of the square root of 2. </summary>
const float R_SQRT_2 = 0.7071067811f;
/// <summary> The reciprical of the square root of 2. </summary>
const double R_SQRT_2_D = 0.70710678118654752440;
/// <summary> The square root of 3. </summary>
const float SQRT_3 = 1.7320508075f;
/// <summary> The square root of 3. </summary>
const double SQRT_3_D = 1.73205080756887729352;
/// <summary> The reciprical of the square root of 3. </summary>
const float R_SQRT_3 = 0.5773502691f;
/// <summary> The reciprical of the square root of 3. </summary>
const double R_SQRT_3_D = 0.57735026918962576450;

/// <summary> The ratio to convert from degrees to radians. </summary>
const float DEG_TO_RAD = PI / 180.0f;
/// <summary> The ratio to convert from degrees to radians. </summary>
const double DEG_TO_RAD_D = PI_D / 180.0;
/// <summary> The ratio to convert from degrees to turns. </summary>
const float DEG_TO_TURN = 1.0f / 360.0f;
/// <summary> The ratio to convert from degrees to turns. </summary>
const double DEG_TO_TURN_D = 1.0 / 360.0;
/// <summary> The ratio to convert from radians to degrees. </summary>
const float RAD_TO_DEG = 180.0f / PI;
/// <summary> The ratio to convert from radians to degrees. </summary>
const double RAD_TO_DEG_D = 180.0 / PI_D;
/// <summary> The ratio to convert from radians to turns. </summary>
const float RAD_TO_TURN = 0.5f / PI;
/// <summary> The ratio to convert from radians to turns. </summary>
const double RAD_TO_TURN_D = 0.5 / PI_D;
/// <summary> The ratio to convert from turns to radians. </summary>
const float TURN_TO_RAD = 2.0f * PI;
/// <summary> The ratio to convert from turns to radians. </summary>
const double TURN_TO_RAD_D = 2.0 * PI_D;
/// <summary> The ratio to convert from turns to degrees. </summary>
const float TURN_TO_DEG = 360.0f;
/// <summary> The ratio to convert from turns to degrees. </summary>
const double TURN_TO_DEG_D = 360.0;

/// <summary> The base of natural logarithms. </summary>
const float E = 2.7182818284f;
/// <summary> The base of natural logarithms. </summary>
const double E_D = 2.71828182845904523536;