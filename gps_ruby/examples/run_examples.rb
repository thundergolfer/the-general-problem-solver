require_relative '../general_problem_solver.rb'

require 'json'

example_files = ['monkeys.json']
example_data = {}

example_files.each do |f|
  data = File.read(f)
  json = JSON.parse(data)
  example_data[f.chomp('.json')] = json
end

def run_menu
  prompt = "Choose one:\n1. Monkeys\nType 'quit' to exit"

  while true
    puts prompt
    choice = gets.chomp
    if choice == 'quit'
      exit 0
    elsif choice.to_i > 0 and choice.to_it <= example_files.length
      break
    end
    puts "Invalid choice! Try again."
  end
  choice
end

while true
  choice = run_menu
  start = example_data[choice]['start']
  finish = example_data[choice]['finish']
  ops = Marshal.load(Marshal.dump(example_data[choice]['ops']))

  actions = gps(start, finish, ops)

  if actions.length > 0
    actions.each do |action|
      puts action
    end
  else
    puts "Couldn't find a solution."
  end
  break
end
