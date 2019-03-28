#encoding:utf-8

require_relative "./lib/ShieldToUI.rb"

module Deepspace
  # Potenciadores de escudo
  class ShieldBooster
    attr_reader :name, :boost, :uses
    
    def initialize(booster_name,booster_value,booster_uses)
      @name = booster_name
      @boost = booster_value
      @uses = booster_uses
    end
   
    def self.newCopy(shield_booster)
      new(shield_booster.name,shield_booster.boost,shield_booster.uses)
    end

    def useIt
      if @uses > 0
        @uses = @uses - 1
        return @boost
      else
        return 1.0
      end
    end

    def getUIversion
      ShieldToUI.new(self)
    end

    def to_s
      getUIversion.to_s
    end

  end
end
