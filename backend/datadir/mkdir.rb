

256.times do |i|
  path = sprintf( "%02x",i)
  Dir.mkdir(path)
  256.times do |j|
    path = sprintf( "%02x/%02x",i,j)
    Dir.mkdir(path)
  end
end