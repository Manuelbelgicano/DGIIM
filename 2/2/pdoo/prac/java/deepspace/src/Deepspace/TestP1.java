/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 * @brief Test de la práctica 1
 */
public class TestP1 {/*
    public static void main(String args[]) {
        // Test de la clase Loot
        System.out.print("\n-----Test de la clase Loot-----\n");
        Loot botin = new Loot(1,2,3,4,5);
        System.out.format("Número de suministros:  %d\n",botin.getNSupplies());
        System.out.format("Número de armas:  %d\n",botin.getNWeapons());
        System.out.format("Número de escudos:  %d\n",botin.getNShields());
        System.out.format("Número de hangares:  %d\n",botin.getNHangars());
        System.out.format("Número de medallas:  %d\n",botin.getNMedals());

        // Test de la clase SuppliesPackage
        System.out.print("\n-----Test de la clase SuppliesPackage-----\n");
        SuppliesPackage suministros = new SuppliesPackage(1.5f,3.4f,2.2f);
        SuppliesPackage suministros2 = new SuppliesPackage(suministros);
        System.out.format("Poder de disparo:  %f\n",suministros2.getAmmoPower());
        System.out.format("Cantidad de combustible:  %f\n",suministros2.getFuelUnits());
        System.out.format("Poder del escudo:  %f\n",suministros2.getShieldPower());
        
        // Test de la clase ShieldBooster
        System.out.print("\n-----Test de la clase ShieldBooster-----\n");
        ShieldBooster escudo = new ShieldBooster("Escudo",3.0f,2);
        ShieldBooster escudo2 = new ShieldBooster(escudo);
        System.out.format("Poder del escudo:  %f\n",escudo2.getBoost());
        System.out.format("Número de usos:  %d\n",escudo2.getUses());
        for (int i=1;i<4;i++) {
            float aux = escudo.useIt();
            System.out.format("Uso número %d: ", i);
            if (aux==1.0f)
                System.out.print("No quedan usos\n");
            else
                System.out.print("Escudo usado\n");
        }
        
        // Test de la clase Weapon
        System.out.print("\n-----Test de la clase Weapon-----\n");
        Weapon arma = new Weapon("Arma",WeaponType.LASER,1);
        Weapon arma2 = new Weapon(arma);
        System.out.format("Tipo de arma:  %s\n",arma2.getType());
        System.out.format("Poder del arma %f\n",arma2.power());
        System.out.format("Número de usos:  %d\n",arma2.getUses());
        for (int i=1;i<3;i++) {
            float aux = arma2.useIt();
            System.out.format("Uso número %d: ", i);
            if (aux==1.0f)
                System.out.print("No quedan usos\n");
            else
                System.out.print("Arma usada\n");
        }
        
        // Test de la clase Dice
        System.out.print("\n-----Test de la clase Dice-----\n");
        Dice dado = new Dice();
        float hangares = 0;
        float escudos = 0;
        for(int i = 0; i < 100; i++){
            hangares += dado.initWithNHangars();
            escudos += dado.initWithNShields();
        }
        System.out.format("Probabilidad de no hangares: %f\n", (100-hangares)/100);
        System.out.format("Probabilidad de no escudos: %f\n", (100-escudos)/100);
        System.out.format("Comienzo con %d armas.\n", dado.initWithNWeapons());
        System.out.format("Empieza el jugador: %d\n", dado.whoStarts(5));
        System.out.format("Primer disparo: %s\n", dado.firstShot());
        System.out.format("¿Se ha movido la nave con velocidad 0.55?: %b\n", dado.spaceStationMoves(0.55f));
    }
*/}
