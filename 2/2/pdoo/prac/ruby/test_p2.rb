#encoding:utf-8

require_relative "./hangar.rb"
require_relative "./damage.rb"
require_relative "./enemystarship.rb"
require_relative "./spacestation.rb"
require_relative "./gameuniverse.rb"

module Deepspace
  class TestP2
    # Test de la clase Hangar
    def self.hangar_test
      puts "Creamos un hangar con 10 espacios disponibles"
      h1 = Hangar.new(10)
      for i in 1..7
        aux_w = Weapon.new("Test",WeaponType::PLASMA,3)
        aux_s = ShieldBooster.new("Test",1.1,3)
        puts "Añadimos arma número #{i}? #{h1.addWeapon(aux_w)}"
        puts "Añadimos escudo número #{i}? #{h1.addShieldBooster(aux_s)}"
      end
      puts "\nCreamos una copia del primer hangar"
      h2 = Hangar.newCopy(h1)
      puts "Información del segundo hangar:"
      puts "#{h2.to_s}"
      for j in 0..2
        puts "Eliminamos el arma y escudos número #{j}:"
        puts "#{h2.removeWeapon(j).to_s}"
        puts "#{h2.removeShieldBooster(j).to_s}"
      end
    end

    # Test de la clase Damage
    def self.damage_test
      puts "Creamos dos daños, uno con un array y otro con un número:"
      d1 = Damage.newNumericWeapons(3,3)
      d2 = Damage.newSpecificWeapons([WeaponType::PLASMA,WeaponType::LASER],3)
      puts "Daño primero:\n #{d1.to_s}"
      puts "Daño segundo:\n #{d2.to_s}"
      puts "\nLos ajustamos con lo siguiente"
      puts " [Weapon.new(\"a\",WeaponType::LASER,1)],[ShieldBooster.new(\"a\",1,1)]"
      d3 = d1.adjust([Weapon.new("a",WeaponType::LASER,1)],[ShieldBooster.new("a",1,1)])
      d4 = d2.adjust([Weapon.new("a",WeaponType::LASER,1)],[ShieldBooster.new("a",1,1)])
      puts "Daño primero:\n #{d3.to_s}"
      puts "Daño segundo:\n #{d4.to_s}"
      puts "\nEliminamos un arma y escudo del daño primero"
      d3.discardWeapon(Weapon.new("b",WeaponType::PLASMA,1))
      d3.discardShieldBooster
      puts "El daño primero no tiene efecto? #{d3.hasNoEffect}"
      puts "El daño segundo no tiene efecto? #{d4.hasNoEffect}"
    end
    
    # Test de la clase EnemyStarShip
    def self.enemystarship_test
      puts "Creamos una nave enemiga"
      e1 = EnemyStarShip.new("Lucky 13",2,3,Loot.new(1,1,1,1,1),Damage.newNumericWeapons(3,3))
      puts "#{e1.to_s}"
      puts "\nPotencia de disparo => #{e1.fire}"
      puts "Potencia de escudo  => #{e1.protection}"
      puts "Aguanta un disparo de potencia 4? #{e1.recieveShot(4)}"
    end

    # Test de la clase SpaceStation
    def self.spacestation_test
      puts "Creamos una estación espacial"
      s1 = SpaceStation.new("ISS",SuppliesPackage.new(1.3,101.0,3.3))
      puts s1.to_s
      puts "\nAñadimos el hangar"
      aux_h = Hangar.new(4)
      aux_h.addWeapon(Weapon.new("Inútil",WeaponType::PLASMA,0))
      aux_h.addWeapon(Weapon.new("Útil",WeaponType::LASER,1))
      aux_h.addShieldBooster(ShieldBooster.new("Inútil",0,0))
      aux_h.addShieldBooster(ShieldBooster.new("Útil",1,1))
      s1.recieveHangar(aux_h)
      puts s1.to_s
      puts "\nEliminamos cosas inútiles del hangar y cargamos las útiles"
      for i in 0..1
        s1.mountShieldBooster(0)
        s1.mountWeapon(0)
      end
      s1.cleanUpMountedUnits()
      puts s1.to_s
      puts "\nEliminamos el hangar y añadimos daño"
      aux_d = Damage.newNumericWeapons(5,5)
      puts aux_d.to_s
      s1.setPendingDamage(aux_d)
      s1.discardHangar()
      puts s1.to_s
      puts "\nLa nave tiene velocidad #{s1.getSpeed}"
      s1.move
      puts "Movemos la nave: 100 => #{s1.fuelUnits}"
      aux_s = SuppliesPackage.new(0.9,0.9,0.9)
      puts "\nAñadimos unos suministros:"
      puts aux_s.to_s
      s1.recieveSupplies(aux_s)
      puts s1.to_s
      puts "La nave está en un estado válido? #{s1.validState}"
    end

    # Test de la clase GameUniverse
    def self.gameuniverse_test
      puts "Creamos un universo:"
      g1 = GameUniverse.new
      # puts g1.to_s
    end
  end
end

puts "\n\n---TEST DE LA CLASE HANGAR---\n\n"
Deepspace::TestP2.hangar_test
puts "\n\n---TEST DE LA CLASE DAMAGE---\n\n"
Deepspace::TestP2.damage_test
puts "\n\n---TEST DE LA CLASE ENEMYSTARSHIP---\n\n"
Deepspace::TestP2.enemystarship_test
puts "\n\n---TEST DE LA CLASE SPACESTATION---\n\n"
Deepspace::TestP2.spacestation_test
puts "\n\n---TEST DE LA CLASE GAMEUNIVERSE---\n\n"
Deepspace::TestP2.gameuniverse_test
