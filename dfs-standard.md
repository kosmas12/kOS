
# DFS Standard
## Key
Each '-' is a byte
'n-' means n bytes
'....' is variable length data

## File index format

### Layout
`<----1><128-2><----3><-4><----5><--------6>`

### Layout key
1) File index (32 bit number)<br>
2) File/Folder? (1 bit - 1 is folder, 0 is file)<br>
3) Name (128 bytes of UTF-8 data)<br>
4) Parent folder (32 bit file index - ignore if first element)<br>
5) CRC-32 (Just for redundancy - you can't actually get the data back from this afaik)<br>
6) Start sector on disk<br>

## File storage format

### Layout
`<----1><--------2><--------3><----4><....5>`

### Layout key
1) File index on table (32bit number)<br>
2) Next sector (64bit number - 0xffffffffffffffff if this is the last sector)<br>
3) Last sector (64bit number - 0xffffffffffffffff if this is the first sector)<br>
4) Length of data on sector<br>
5) Data<br>
