ffmpeg -i ./Bridge.of.Spiers.2015.DUAL.BDRip.2,91Gb.XviD.AC3.avi -f webm -vcodec libvpx -acodec libvorbis -b 600k -r 25 -s 320x240 -ar 44100 -ab 128k -ac 2 -y   -map 0:0 -map 0:2  ./output.webm
