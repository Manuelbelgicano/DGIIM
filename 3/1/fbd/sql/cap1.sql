CREATE TABLE prueba1 (
    cad char(3),
    n int,
    x float);

CREATE TABLE prueba2 (
    cad1 char(8),
    num int);

DESCRIBE prueba1;
DESCRIBE prueba2;

DROP TABLE prueba1;

CREATE TABLE plantilla(
    dni varchar2(9),
    nombre varchar2(15),
    estadocivil varchar2(10)
    CHECK (estadocivil IN ('soltero', 'casado', 'divorciado', 'viudo')),
    fechaalta date,
    PRIMARY KEY (dni)
);

ALTER TABLE plantilla ADD (
    fechabaja date
);
DESCRIBE plantilla;

ALTER TABLE ventas ADD (
    fecha date
);

DESCRIBE ventas;