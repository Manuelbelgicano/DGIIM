#encoding:utf-8

require_relative "spacestation"

module Deepspace

  class SpaceCity<SpaceStation

    attr_reader :collaborators

    def initialize(base,rest)
      newCopy(base)
      @base = base
      @collaborators = rest
    end

    def fire
      fire_power = super
      collaborators.each do |station|
        fire_power += station.fire
      end
      return fire_power
    end

    def protection
      shield_power = super
      collaborators.each do |station|
        shield_power += station.protection
      end
      return shield_power
    end

    def setLoot(loot)
      super
      return Transformation::NOTRANSFORM
    end

    def to_s
      aux = "-----CIUDAD ESPACIAL-----\nBASE\n"
      aux += super
      aux += "\nCOLABORADORES\n"
      collaborators.each do |station|
        aux += station.to_s
      end
      return aux
    end
  end
end

