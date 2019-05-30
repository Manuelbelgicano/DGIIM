/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;
/**
 * @brief Clase de test de la práctica 2
 */
public class TestP2 {
    public static void main(String args[]) {
        //Test de la clase Hangar
        Hangar h1 = new Hangar(4);
        Weapon w_aux = new Weapon("Arma_test",WeaponType.LASER,1);
        ShieldBooster s_aux = new ShieldBooster("Escudo_test",3.0f,1);
        for (int i=0;i<3;i++) {
            System.out.format("Vuelta nº %d\n", i+1);
            if (h1.addWeapon(w_aux))
                System.out.print("Arma añadida\n");
            if (h1.addShieldBooster(s_aux))
                System.out.print("Escudo añadido\n");
        }
        System.out.print("\n\n" + h1.toString());
        Hangar h2 = new Hangar(h1);
        System.out.print("\nEliminamos las armas y escudos");
        h2.removeShieldBooster(0);
        h2.removeShieldBooster(0);
        h2.removeWeapon(0);
        h2.removeWeapon(0);
        System.out.print("\n\n" + h2.toString());
        
        //Test de la clase Damage
       // Damage d1 = new Damage(6,6);
        ArrayList<WeaponType> wt_aux = new ArrayList<>();
        wt_aux.add(WeaponType.LASER);
        wt_aux.add(WeaponType.PLASMA);
        wt_aux.add(WeaponType.LASER);
        //Damage d2 = new Damage(wt_aux,0);
        //System.out.print("\nDaños:\n" + d1.toString());
        //System.out.print("\n----------\n" + d2.toString());
        
        //Test de la clase SpaceStation
        SpaceStation s1= new SpaceStation("ISS", new SuppliesPackage(1,1,1));
        System.out.print("\n\n" + s1.toString());
        s1.recieveHangar(h1);
        s1.mountShieldBooster(0);
        s1 .mountWeapon(0);
        System.out.print("\n\n" + s1.toString());
        s1.recieveWeapon(w_aux);
        s1.recieveShieldBooster(s_aux);
        s1.recieveSupplies(new SuppliesPackage(200,200,200));
        //s1.setPendingDamage(d1);
        System.out.print("\nDAÑO_1\n" + s1.toString());
        //s1.setPendingDamage(d2);
        System.out.print("\nDAÑO_2\n" + s1.toString());
    }
}
