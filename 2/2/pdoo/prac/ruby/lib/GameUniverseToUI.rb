#encoding:utf-8

module Deepspace

# 19.4.17 - Translation from Java
# @author Profe
  
class GameUniverseToUI 
  
  attr_reader :currentStation, :currentEnemy
    
    def initialize (station,enemy) 
        @currentStation = station.getUIVersion()
        @currentEnemy= enemy.getUIVersion()
    end

    public
    
    def to_s
      out = "Estación actual -> #{@currentStation}\n"
      out +="Enemigo actual --> #{@currentEnemy}"
      return out
    end
    
    
end # class

end # module
