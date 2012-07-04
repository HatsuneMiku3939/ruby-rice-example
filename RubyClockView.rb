if $0 != "embedded"
	puts "WARNING: this script is supposed "\
		 "to be run only from 'embedded'"
	exit 1
end

class ClockView < AbstractView
	def initialize
		super
		puts "Instantiation ClockView from RUBY"	
	end

	def update(model)
		print "                              \r#{model.hour}:#{model.minute}:#{model.second}\r"
	end
end
