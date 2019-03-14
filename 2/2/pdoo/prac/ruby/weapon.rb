#encoding:utf-8
module Deepspace
  # Armas de la estación
  class Weapon
    attr_reader :type, :uses

    def initialize(weapon_name,weapon_type,weapon_uses)
      @name = weapon_name
      @type = weapon_type
      @uses = weapon_uses
    end

    def self.newCopy(weapon)
      new(weapon.name,weapon.type,weapon.uses)
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
