#encoding:utf-8

require "./lib/DamageToUI.rb"

module Deepspace
  # Daño
  class Damage

    attr_reader :nShields

    def initialize(s)
      @nShields = s
    end

    def to_s
      getUIversion.to_s
    end

    # Elimina un potenciador de escudo
    def discardShieldBooster
      if @nShields>0
        @nShields -= 1
      end
    end

    # Comprueba si el daño no tiene efecto
    def hasNoEffect
      return @nShields==0
    end
  end
end
