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

  module WeaponType
    class Type
      def initialize(power_val)
        @power = power_val
      end
      attr_reader :power
   end
    LASER = Type.new(2.0)
    MISSILE = Type.new(3.0)
    PLSMA = Type.new(4.0)
  end
end
