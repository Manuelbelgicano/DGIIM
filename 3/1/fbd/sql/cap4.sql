create view proovedores_londres as
    select codpro,nompro,status from proveedor where
        ciudad='Londres';

insert into proovedores_londres ('S','Jose Suarez',3,'Granada');

create view ciudades_proveedores as
    select nompro,ciudad from proveedor;

insert into ciudades_proveedores values ('Margarita Belancourt','Pamplona');

create view vista1 as
    select x.codpro,x.nompro,y.codpj from proveedor x, ventas y where y.codpie in (
        select z.codpie from pieza z where z.color='Gris');