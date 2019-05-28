#encoding:utf-8

require_relative "dice"
require_relative "powerefficientspacestation"

module Deepspace

  class BetaPowerEfficientSpaceStation<PowerEfficientSpaceStation
    
    @@EXTRAEFFICIENCY = 1.2

    def initialize(station)
      newCopy(station)
    end

    def fire
      dice = Dice.new
      if dice.extraEfficiency
        return super*@@EXTRAEFFICIENCY
      else
        return super
      end
    end
  end
end
