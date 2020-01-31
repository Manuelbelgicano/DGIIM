select distinct ciudad from proyecto;

select codpro,codpie,codpj from ventas;

select * from pieza where (ciudad='Madrid' and (color='Gris' or color='Rojo'));

select * from ventas where (cantidad>=200 and cantidad<=300);

select * from pieza where (nompie like '%ornillo');

select table_name from all_tables where table_name like '%ventas';
select table_name from all_tables where table_name like upper('%ventas');
select table_name from all_tables where table_name like lower('%ventas');

(select distinct ciudad from proveedor where (status>2)) minus (select distinct ciudad from pieza where (codpie='P1'));

(select codpj from ventas) minus (select codpj from ventas where (codpro!='S1'));

(select distinct ciudad from proveedor) union 
(select distinct ciudad from pieza) union 
(select distinct ciudad from proyecto);

(select distinct ciudad from proveedor) union all 
(select distinct ciudad from pieza) union all 
(select distinct ciudad from proyecto);

select * from proveedor, ventas;

select ventas.codpro,ventas.codpie,ventas.codpj from proveedor,pieza,proyecto,ventas where (
    (proveedor.codpro=ventas.codpro and pieza.codpie=ventas.codpie and proyecto.codpj=ventas.codpj) and
    (proveedor.ciudad=pieza.ciudad) and (pieza.ciudad=proyecto.ciudad)
);

select P1.codpro,P2.codpro from proveedor P1,proveedor P2 where (P1.ciudad!=P2.ciudad);

(select codpie from pieza) minus
(select Y.codpie from pieza X,pieza Y where (X.peso>Y.peso));

select distinct codpie from ventas X natural join (select * from proveedor where ciudad='Madrid') Y;

select distinct ciudad,codpie from pieza natural join (
    select y.codpie from ventas y, proveedor z, proyecto t where (
        y.codpro=z.codpro and y.codpj=t.codpj and z.ciudad=t.ciudad)
);

SELECT nompro FROM proveedor ORDER BY nompro;
SELECT nompro FROM proveedor;

select distinct codpie from ventas where codpro in (
    select codpro from proveedor where ciudad='Madrid'
);

select codpj from proyecto where ciudad in (
    select ciudad from pieza
);

select distinct codpj from proyecto where codpj not in (
    select codpj from ventas x,pieza y,proveedor z where (
        x.codpie=y.codpie and x.codpro=z.codpro and y.color='Rojo' and z.ciudad='Londres')
);

select codpie from pieza where peso > all (
    select peso from pieza where nompie='Tornillo'
);

select * from pieza where peso >= all (
    select peso from pieza
);

select codpie from pieza where not exists (
    (select codpj from proyecto where ciudad='Londres') minus
    (select distinct ventas.codpj from ventas,proyecto where pieza.codpie=ventas.codpie and proyecto.codpj=ventas.codpj and ciudad='Londres')
);

select codpro from proveedor where not exists (
    (select distinct codpie from pieza x,proyecto y where x.ciudad=y.ciudad) minus
    (select distinct codpie from ventas where proveedor.codpro=ventas.codpro)
);

select count(*) from ventas where cantidad>1000;

select max(peso) from pieza;

select codpie from pieza where peso >= all (
    select max(p.peso) from pieza p
);

select codpro from proveedor where (select count(*) from ventas where proveedor.codpro=ventas.codpro)>3;

select trunc(avg(cantidad),2),nompie,codpie from (select cantidad,codpie from ventas) natural join (select codpie,nompie from pieza) group by nompie, codpie;

select avg(cantidad),codpro from ventas where codpie='P1' group by codpro;

select sum(cantidad),codpie,codpj from ventas group by (codpie,codpj) order by codpj,codpie;

SELECT s.nompro
FROM ventas v, proveedor s
WHERE v.codpro = s.codpro
GROUP BY (v.codpro)
HAVING sum(v.cantidad) > 1000;

select x.nompro from proveedor x,ventas y where x.codpro=y.codpro group by x.nompro having sum(y.cantidad)>1000;

select x.nompie from pieza x,ventas y where x.codpie=y.codpie group by x.nompie having sum(y.cantidad)=(
    select max(sum(z.cantidad)) from ventas z group by z.codpie);

select x.codpro from ventas x group by x.codpro having sum(x.cantidad)>(
    select sum(y.cantidad) from ventas y where y.codpro='S1');

select x.codpro,sum(x.cantidad) from ventas x group by x.codpro order by sum(x.cantidad) desc;

-- 3.44 no lo se hacer

select codpro from ventas group by codpro having count(codpro)>10;

select distinct x.codpro from ventas x where not exists (
    (select distinct y.codpie from ventas y where y.codpro='S1') minus
    (select distinct z.codpie from ventas z where z.codpro=x.codpro)
);

select x.codpro,count(x.codpie) from ventas x where not exists (
    (select distinct y.codpie from ventas y where y.codpro='S1') minus
    (select distinct z.codpie from ventas z where z.codpro=x.codpro)
) group by x.codpro;

select distinct x.codpj from ventas x where not exists (
    (select distinct y.codpro from ventas y where y.codpie='P3') minus
    (select distinct z.codpro from ventas z where z.codpj=x.codpj)
);

select x.codpj,avg(x.cantidad) from ventas x where not exists (
    (select distinct y.codpro from ventas y where y.codpie='P3') minus
    (select distinct z.codpro from ventas z where z.codpj=x.codpj)
) group by x.codpj;

select avg(cantidad),to_char(fecha,'yyyy'),codpro from ventas group by to_char(fecha,'yyyy'),codpro order by codpro,to_char(fecha,'yyyy');

select distinct x.codpro from ventas x, pieza y where x.codpie=y.codpie and y.color='Rojo';

select distinct x.codpro from ventas x where not  exists (
    (select distinct y.codpie from pieza y where y.color='Rojo') minus
    (select distinct z.codpie from ventas z where x.codpro=z.codpro)
);

select distinct x.codpro from ventas x where not exists (
    select distinct y.codpie from pieza y,ventas z where z.codpro=x.codpro and y.color!='Rojo');
    
select distinct x.codpro from ventas x, pieza y where x.codpie=y.codpie and y.color='Rojo' and exists (
    select z.codpj from ventas z,pieza w where x.codpro=z.codpro and z.codpie=w.codpie and w.color='Rojo' and w.codpie!=y.codpie);
    
select distinct x.codpro from ventas x where not  exists (
    (select distinct y.codpie from pieza y where y.color='Rojo') minus
    (select distinct z.codpie from ventas z where x.codpro=z.codpro)
) group by x.codpro having sum(x.cantidad)>10;

update proveedor set
    status = 1
where codpro in (
    select distinct codpro from ventas where codpie='P1');
    
-- 3.59 paso