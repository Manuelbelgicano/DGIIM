/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 * @brief Test de la práctica 1
 */
public class TestP1 {
    public static void main(String args[]) {
        // Test de la clase Loot
        System.out.format("\n-----Test de la clase Loot-----\n");
        Loot botin = new Loot(1,2,3,4,5);
        System.out.format("Número de suministros:  %d\n",botin.getNSupplies());
        System.out.format("Número de armas:  %d\n",botin.getNWeapons());
        System.out.format("Número de escudos:  %d\n",botin.getNShields());
        System.out.format("Número de hangares:  %d\n",botin.getNHangars());
        System.out.format("Número de medallas:  %d\n",botin.getNMedals());

        // Test de la clase SuppliesPackage
        System.out.format("\n-----Test de la clase SuppliesPackage-----\n");
        SuppliesPackage suministros = new SuppliesPackage(1.5f,3.4f,2.2f);
    }
}
