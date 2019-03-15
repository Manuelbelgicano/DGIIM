#encoding:utf-8

require_relative "./combatresult.rb"
require_relative "./dice.rb"
require_relative "./gamecharacter.rb"
require_relative "./loot.rb"
require_relative "./shieldbooster.rb"
require_relative "./shotresult.rb"
require_relative "./suppliespackage.rb"
require_relative "./weapon.rb"
require_relative "./weapontype.rb"

module Deepspace
  class TestP1
    def self.main
      puts "Clase 'Loot':"
      l1 = Loot.new(1,2,3,4,5)
      l2 = Loot.new(5,4,3,2,1)
      puts "El botín 1 tiene: #{l1.nSupplies} #{l1.nWeapons} #{l1.nShields} #{l1.nHangars} #{l1.nMedals}"
      
      puts "Clase 'SuppliesPackage':"
      sp1 = SuppliesPackage.new(1.9,2.8,3.7)
      sp2 = SuppliesPackage.newCopy(sp1)
      puts "El paquete 2 tiene: #{sp2.ammoPower} #{sp2.fuelUnits} #{sp2.shieldPower}"

      puts "Clase 'ShieldBooster':"
      sb1 = ShieldBooster.new("Escudo del poder maximo de la destruccion de los planetas",1.2,3)
      sb2 = ShieldBooster.newCopy(sb1)
      puts "#{sb1.name} tiene como valores: #{sb1.boost} #{sb1.uses}"
      for i in 0..5
        puts "Usando el escudo #{sb2.name}: #{sb2.useIt}"
      end

      puts "Clase 'Weapon':\n"
      w1 = Weapon.new("Espatula",WeaponType::PLASMA,3)
      w2 = Weapon.new("Cuchara",WeaponType::LASER,2)
      puts "Arma 1: poder = #{w1.power}"
      for i in 0..5
        puts "Usando el arma 2: #{w2.useIt}"
      end

      puts "Clase 'Dice':"
      d = Dice.new
      aux1 = 0
      aux2 = 0
      for i in 0..99
        aux1 = aux1 + d.initWithNHangars
        aux2 = aux2 + d.initWithNShields
      end
      puts "Se ha comenzado sin hangares #{100-aux1}/100"
      puts "Se ha comenzado sin escudos #{100-aux2}/100"
      puts "Se ha comenzado con #{d.initWithNWeapons} armas"
      puts "Empieza el jugador #{d.whoStarts(5)} de un total de 5 jugadores"
      puts "Dispara primero #{d.firstShot}"
      if d.spaceStationMoves(0.55)
        puts "La nave con una velocidad 0.55 se mueve"
      else
        puts "La nave con una velocidad 0.55 no se mueve"
      end
    end
  end
end

Deepspace::TestP1.main
