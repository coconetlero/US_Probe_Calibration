function jac = jacmodhs76(p)
  m=4;

  jac(1, 1:m)=[1.0, 0.0, 0.0, 0.0];
  jac(2, 1:m)=[0.0, sqrt(0.5), 0.0, 0.0];
  jac(3, 1:m)=[0.0, 0.0, 1.0, 0.0];
  jac(4, 1:m)=[0.0, 0.0, 0.0, sqrt(0.5)];
