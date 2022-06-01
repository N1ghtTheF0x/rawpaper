const fs = require("fs")
const path = require("path")

const FILE_EXT = ".wfs"

const files = process.argv.slice(2,-1)
const _output = process.argv[process.argv.length-1]
const output = _output.endsWith(FILE_EXT) ? _output : _output + ".wfs"

const idSize = 6
const idText = "WOODFS"

const fileCountSize = 8
const fileCount = BigInt(files.length)

function getFileInfo(file)
{
    const filepath = path.resolve(process.cwd(),file)
    const data = fs.readFileSync(filepath)
    const fileStats = fs.statSync(filepath)
    const type = path.extname(file).substring(1)
    const typeSize = type.length
    return {
        typeLength: typeSize,
        type: type,
        fileSize: fileStats.size,
        data: data
    }
}

const fileinfo = []
for(const file of files) fileinfo.push(getFileInfo(file))

function getFileInfoSize(fileinfo)
{
    var size = 0
    for(const info of fileinfo)
    {
        size += 4 + 8 + info.typeLength + info.fileSize
    }
    return size
}

const fileinfoSize = getFileInfoSize(fileinfo)

const buffer = Buffer.alloc(idSize + fileCountSize + fileinfoSize)

var offset = 0

buffer.write(idText,offset,idSize,"ascii")
offset += idSize

buffer.writeBigUInt64LE(fileCount,offset)
offset += fileCountSize

for(const file of fileinfo)
{
    buffer.writeUInt32LE(file.typeLength,offset)
    offset += 4

    buffer.write(file.type,offset)
    offset += file.typeLength

    buffer.writeBigUInt64LE(BigInt(file.fileSize),offset)
    offset += 8

    buffer.write(file.data.toString("base64"),offset,file.fileSize,"base64")
    offset += file.fileSize
}

fs.writeFileSync(path.resolve(process.cwd(),output),buffer)