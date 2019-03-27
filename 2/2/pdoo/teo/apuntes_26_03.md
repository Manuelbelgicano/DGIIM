## Apuntes de clase de PDOO

```ruby
class Lio
    @@duda = 3
    @duda = 33
    
    def initialize
        @duda = 333
    end
    
    attr_reader :duda
    
    def de_instancia
        puts @duda + 1 # 334
        puts @@duda # 3
        puts self.class.duda + 1 # 34
    end
    
    def self.duda
        puts @duda
    end
    
    def problema(a)
        puts a.duda
    end
end

class Pepe
    def duda
        "Hola"
    end
end

puts Lio.new.duda # 333
puts Lio.duda # 33
Lio.new.problema(Lio.new) # 333
Lio.new.problema(Pepe.new) # Hola
```

| Ámbito de clase | Ámbito de instancia |
| --------------- | ------------------- |
| @@duda = 3      | @duda = 333         |
| @duda = 3       |                     |

Atibutos de clase = Atributos de instancia de clase (por ahora, en herencia veremos las diferencias)