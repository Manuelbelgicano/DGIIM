#encoding:utf-8

require_relative "./spacestation.rb"
require_relative "./gameuniverse.rb"

module Deepspace
  class TestP3
    # Test de la clase spacestation
    def self.spacestation_test
      s = SpaceStation.new("ISS",SuppliesPackage.new(2,100,2))
      h = Hangar.new(2)
      h.addWeapon(Weapon.new("Arma",WeaponType::PLASMA,2))
      h.addShieldBooster(ShieldBooster.new("Escudo",2,2))
      s.recieveHangar(h)
      s.mountWeapon(0)
      s.mountShieldBooster(0)
      puts s.to_s

      puts "Disparo de la nave: #{s.fire}"
      puts "Escudo de la nave: #{s.protection}"
      puts "La nave recibe un disparo de poder 2. ¿Aguanta? #{s.recieveShot(2.0)}"
      
      d = Damage.newSpecificWeapons([WeaponType::PLASMA],1)
      puts "Daño a añadir a la nave:"
      puts d.to_s
      s.setPendingDamage(d)
      puts s.to_s

      puts "Descartamos el arma y el escudo"
      s.discardShieldBooster(0)
      s.discardWeapon(0)
      puts s.to_s
      
      l = Loot.new(1,1,1,1,1)
      puts "Botín a añadir a la nave:"
      puts l.to_s
      s.setLoot(l)
      puts s.to_s
    end
    # Test de la clase gameuniverse
    def self.gameuniverse_test
      g = GameUniverse.new
      s = SpaceStation.new("Satélite",SuppliesPackage.new(0,0,0))
      e = EnemyStarShip.new("Nave del caos",1,1,Loot.new(1,1,1,1,1),Damage.newNumericWeapons(2,2))
      puts "Hacemos combatir la nave:"
      puts s.to_s
      puts "con el enemigo:"
      puts e.to_s
      puts "¿Ganador? #{g.combatGo(s,e)}"
    end
  end
end

puts "\n\n---TEST DE LA CLASE SPACESTATION---\n\n"
Deepspace::TestP3.spacestation_test
puts "\n\n---TEST DE LA CLASE GAMEUNIVERSE---\n\n"
Deepspace::TestP3.gameuniverse_test
