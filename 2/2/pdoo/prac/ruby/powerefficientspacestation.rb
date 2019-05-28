#encoding:utf-8

require_relative "spacestation"

module Deepspace

  class PowerEfficientSpaceStation<SpaceStation

    @@EFFICIENCYFACTOR = 1.10

    def initialize(station)
      newCopy(station)
    end

    def fire
      return super*@@EFFICIENCYFACTOR
    end

    def protection
      return super*@@EFFICIENCYFACTOR
    end

    def setLoot(loot)
      super
      if loot.getEfficient==true
        return Transformation::GETEFFICIENT
      else
        return Transformation::NOTRANSFORM
      end
    end

    def to_s
      aux = "-----POWER EFFICIENT SPACE STATION-----\n"
      aux += super
      return aux
    end
  end
end

