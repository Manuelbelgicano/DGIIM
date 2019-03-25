#encoding:utf-8

require_relative "./lib/DamageToUI.rb"

module Deepspace
  # Daño
  class Damage

    attr_reader :nWeapons, :weapons, :nShields

    def initialize(w,wl,s)
      @nWeapons = w
      @weapons = wl
      @nShields = s
    end
    
    # Constructor de daño con número genérico de armas
    def self.newNumericWeapons(w,s)
      Damage.new(w,nil,s)
    end

    # Constructor de daño con tipo específico de armas
    def self.newSpecificWeapons(wl,s)
      Damage.new(0,wl,s)
    end

    def getUIVersion
      DamageToUI.new(self)
    end
    
    # Comprueba si el array 'w' contiene armas del tipo 't'
    private def arrayContainsType(w,t)
      w.each_index do |i|
        if w[i].type==t
          return i
        end
      end
      return -1
    end

    # Ajusta el objeto al equipo del jugador
    def adjust(w,s)
      if s.length<@nShields
        newNShields = s.length
      else
        newNShields = @nShields
      end
      if @nWeapons==0
        newWeapons = Array.new(@weapons)
        newWeapons.each do |type|
          if arrayContainsType(w,type)==-1
            newWeapons.delete(type)
          end
        end
        return newSpecificWeapons(newWeapons,newNShields)
      elsif @weapons==nil
        if w.length<@nWeapons
          newNWeapons = w.length
        else
          newNWeapons = @nWeapons
        end
        return newNumericWeapons(newNWeapons,newNShields)
      end
    end

    # Elimina un arma del daño
    def discardWeapon(w)
      if @weapons!=nil
        index = arrayContainsType(@weapons,w.type)
        if index!=-1
          @weapons.delete_at(index)
        end
      elsif @nWeapons>0
        @nWeapons -= 1
      end
    end

    # Elimina un potenciador de escudo
    def discardShieldBooster
      if @nShields>0
        @nShields -= 1
      end
    end

    # Comprueba si el daño no tiene efecto
    def hasNoEffect
      if @weapons.lenght==0 and @nWeapons==0 and @nShields==0
        return true
      else
        return false
      end
    end
  end
end
