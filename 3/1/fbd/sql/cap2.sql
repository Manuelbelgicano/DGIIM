insert into prueba2 values ('prueba',11);
insert into prueba2 values ('proeba',22);
insert into prueba2 values ('preuba',33);
INSERT INTO plantilla (dni,nombre,estadocivil,fechaalta)
    VALUES ('12345678','Pepe','soltero', SYSDATE);
INSERT INTO plantilla (dni,nombre,estadocivil,fechaalta)
    VALUES ('87654321','Juan', 'casado', SYSDATE);
INSERT INTO plantilla (dni, estadocivil) 
    VALUES ('11223344','soltero');  
select * from prueba2;
select DNI, nombre, estadocivil from plantilla;

update plantilla set
    nombre = 'Luis'
    where dni='12345678';
select DNI, nombre from plantilla;

select * from ventas;
INSERT INTO ventas VALUES ('S3', 'P1', 'J1', 150, '24/12/05');
INSERT INTO ventas (codpro, codpj) VALUES ('S4', 'J2');
INSERT INTO ventas VALUES('S5','P3','J6',400,TO_DATE('25/12/00'));

select codpro, fecha from ventas;
update ventas set
    fecha = to_date(2005,'yyyy')
    where codpro='S5';
select codpro, fecha from ventas;

select to_char(fecha,'"Dia" day,dd/mm/yy') from ventas;

delete from ventas;
delete from pieza;
delete from proveedor;
delete from proyecto;
drop table plantilla;
drop table prueba2;