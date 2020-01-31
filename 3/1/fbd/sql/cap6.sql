CREATE CLUSTER cluster_codpro(codpro VARCHAR2(3));
CREATE TABLE proveedor2(
codpro VARCHAR2(3) PRIMARY KEY,
nompro VARCHAR2(30) NOT NULL,
status NUMBER(2) CHECK(status>=1 AND status<=10),
ciudad VARCHAR2(15))
CLUSTER cluster_codpro(codpro);
CREATE TABLE ventas2(
codpro VARCHAR2(3) REFERENCES proveedor2(codpro),
codpie REFERENCES pieza(codpie),
codpj REFERENCES proyecto(codpj),
cantidad NUMBER(4),
fecha DATE,
PRIMARY KEY (codpro,codpie,codpj))
CLUSTER cluster_codpro(codpro);
CREATE INDEX indice_cluster ON CLUSTER cluster_codpro;
insert into proveedor2 (codpro,nompro,status,ciudad)
    values ('S1','Jose Fernandez',2,'Madrid');
insert into proveedor2 (codpro,nompro,status,ciudad)
    values ('S2','Manuel Vidal',1,'Londres');
insert into proveedor2 (codpro,nompro,status,ciudad)
    values ('S3','Luisa Gomez',3,'Lisboa');
insert into proveedor2 (codpro,nompro,status,ciudad)
    values ('S4','Pedro Sanchez',4,'Paris');
insert into proveedor2 (codpro,nompro,status,ciudad)
    values ('S5','Maria Reyes',5,'Roma');
insert into ventas2 select * from opc.ventas;

select codpro from ventas2 where codpj='J1';