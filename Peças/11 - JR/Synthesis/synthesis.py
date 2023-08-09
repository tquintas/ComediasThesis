import os,sys
file_dir=os.path.dirname(__file__)
sys.path.append(file_dir)
import side_chain as sc

def synth(specify_rest=str,rest_prob=int,dna_seq=str,series=str,instrument_name=str,instrument_amplitude=str):
        """Create a ly file for one instrument"""
        music=sc.new(specify_rest,rest_prob,dna_seq,series,instrument_name,instrument_amplitude)
        lily="""
\\version "2.23.5"

\\layout {
        \\context {
                \\Voice
                \\remove "Note_heads_engraver"
                \\consists "Completion_heads_engraver"
                \\remove "Rest_engraver"
                \\consists "Completion_rest_engraver"
        }
}

music = { \\absolute {
"""+music+"""}
}

\\new Staff \\with { instrumentName= """+'"'+sc.instr_name+'"'+""" } {
                \\time 4/4
                \\set completionUnit = #(ly:make-moment 1/4)
                \\music
}
"""
        num=1
        while True:
                try:
                        with open(file_dir+"/synthesis{}.ly".format(num),"x") as f:
                                f.write(lily)
                        break
                except FileExistsError:
                        num+=1
                        continue
        print("Process completed.")
        return

def poly_synth(paper_size='a4',paper_orientation='landscape',staff_size=float,specify_rest=str,rest_prob=int,dna_seq=str,series=str,amp=str,number_of_instruments=int):
        """Create a ly file for multiple instruments"""
        if number_of_instruments==int or type(number_of_instruments)!=int:
                number_of_instruments=int(input('Number of instruments: '))
        music=''
        staffs=[]
        newstaffs=[]
        name=''
        names=[]
        for i in range(number_of_instruments):
                name=input('Name of instrument number {}: '.format(i+1))
                names.append(name)
                music=sc.new(specify_rest,rest_prob,dna_seq,series,name,amp)
                staffs.append(name.lower().replace(' ','')+' = { \\absolute {\n'+music+'\n}\n}')
                newstaffs.append("""
                \\new Staff \\with { instrumentName= """+'"'+sc.instr_name+'"'+""" } {
                        \\time 4/4
                        \\set completionUnit = #(ly:make-moment 1/4)
                        \\"""+name.lower().replace(' ','')+"""
                        }""")              
        lily="""
\\version "2.23.5"

#(set-global-staff-size """+str(round(staff_size*20))+""")

\\layout {
        #(set-default-paper-size """+'"'+paper_size+paper_orientation+'"'+""")
        \\context {
                \\Voice
                \\remove "Note_heads_engraver"
                \\consists "Completion_heads_engraver"
                \\remove "Rest_engraver"
                \\consists "Completion_rest_engraver"
        }
}

"""+'\n'.join(staffs)+"""

\\score {
        \\new StaffGroup <<
"""+''.join(newstaffs)+"""
        >>
}
"""
        num=1
        while True:
                try:
                        with open(file_dir+"/synthesis{}.ly".format(num),"x") as f:
                                f.write(lily)
                        break
                except FileExistsError:
                        num+=1
                        continue
        print("Process completed.")
        return
