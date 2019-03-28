#encoding:utf-8

module ModuloExamen
	class Figura
	
		@@nFiguras = 0
				
		def initialize(r,l1,l2)
			@radio = r
			@lado1 = l1
			@lado2 = l2
			@@nFiguras += 1
		end
		
		def self.newCircle(r)
			new(r,-1,-1)
		end
		
		def self.newRectangle(l1,l2)
			new(-1,l1,l2)
		end
		
		def self.nFiguras
			@@nFiguras
		end
		
		def area
			if @radio==-1
				area = @lado1 * @lado2
			else
				area = @radio * @radio * Math::PI
			end
			return area
		end
		
		private_class_method :new

	end
end
