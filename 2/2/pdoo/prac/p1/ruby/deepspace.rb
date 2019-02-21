#encoding:utf-8
module Deepspace
  # Resultados posibles de un combate
  module CombatResult
    ENEMYWINS = :enemywins
    NOCOMBAT = :nocombat
    STATIONSCAPES = :stationscapes
    STATIONWINS = :stationwins
  end
  
  # Tipos de personajes
  module GameCharacter
    ENEMYSTARSHIP = :enemystarship
    SPACESTATION = :spacestation
  end

  # Resultados posibles de un disparo
  module ShotResult
    DONOTRESIST = :donotresist
    RESIST = :resist
  end
  
  # Tipos de armas
  module WeaponType
    class Type
      attr_reader :power

      def initialize(power_val)
        @power = power_val
      end
   end

    LASER = Type.new(2.0)
    MISSILE = Type.new(3.0)
    PLSMA = Type.new(4.0)
  end

  # Botín
  class Loot
    attr_reader :nSupplies, :nWeapons, :nShields, :nHangars, :nMedals

    def initialize(supplies_num,weapons_num,shields_num,hangars_num,medals_num)
      @nSupplies = supplies_n
      @nWeapons = weapons_n
      @nShields = shields_n
      @nHangars = hangars_num
      @nMedals = medals_num
    end
  end
  
  # Paquete de suministros
  class SuppliesPackage
    attr_reader :ammoPower, :fuelUnits, :shieldPower
    
    def initialize(ammo_p,fuel_u,shield_p)
      @ammoPower = ammo_p
      @fuelUnits = fuel_u
      @shieldPower = shield_p
    end
    
    def self.newCopy(supplies_package)
      copy = SuppliesPackage.new(supplies_package.ammoPower,supplies_package.fuelUnits,supplies_package.shieldPower)
      return copy
    end
  end
  
  # Potenciadores de escudo
  class ShieldBooster
    attr_reader :name, :boost, :uses
    
    def initialize(booster_name,booster_value,booster_uses)
      @name = booster_name
      @boost = booster_value
      @uses = booster_uses
    end
   
    def self.newCopy(shield_booster)
      copy = ShieldBooster.new(shield_booster.name,shield_booster.boost,shield_booster.uses)
      return copy
    end

    def useIt
      if @uses > 1
        @uses = @uses - 1
        return @boost
      else
        return 1.0
      end
    end
  end

  # Armas de la estación
  class Weapon
    attr_reader :type, :uses

    def initialize(weapon_name,weapon_type,weapon_uses)
      @name = weapon_name
      @type = weapon_type
      @uses = weapon_uses
    end

    def self.newCopy(weapon)
      copy = Weapon.new(weapon.name,weapon.type,weapon.uses)
      return copy
    end
  
    def power
      @type.power
    end

    def useIt
      if @uses > 1
        @uses = @uses - 1
        return power
      else
        return 1.0
      end
    end
  end
end
