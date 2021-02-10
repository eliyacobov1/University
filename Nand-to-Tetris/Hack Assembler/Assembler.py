import sys
import os
import collections

A_INSTRUCTION_PREFIX = "@"
ASM_SUFFIX = ".asm"
HACK_SUFFIX = ".hack"

Symbols = {'R0': 0, 'R1': 1, 'R2': 2, 'R3': 3,
           'R4': 4, 'R5': 5, 'R6': 6, 'R7': 7,
           'R8': 8, 'R9': 9, 'R10': 10, 'R11': 11,
           'R12': 12, 'R13': 13, 'R14': 14, 'R15': 15,
           'SCREEN': 16384, 'KBD': 24576, 'SP': 0,
           'LCL': 1, 'ARG': 2, 'THIS': 3, 'THAT': 4}

destination = {"": "000", "M": "001", "D": "010", "MD": "011",
               "A": "100", "AM": "101", "AD": "110", "AMD": "111"}

jump = {"": "000", "JGT": "001", "JEQ": "010", "JGE": "011",
        "JLT": "100", "JNE": "101", "JLE": "110", "JMP": "111"}

comp = {"0": "0101010", "1": "0111111", "-1": "0111010", "D": "0001100",
        "A": "0110000", "!D": "0001101", "!A": "0110001", "-D": "0001111",
        "-A": "0110011", "D+1": "0011111", "A+1": "0110111", "D-1": "0001110",
        "A-1": "0110010", "D+A": "0000010", "D-A": "0010011", "A-D": "0000111",
        "D&A": "0000000", "D|A": "0010101", "M": "1110000", "!M": "1110001",
        "-M": "1110011", "M+1": "1110111", "M-1": "1110010", "D+M": "1000010",
        "D-M": "1010011", "M-D": "1000111", "D&M": "1000000", "D|M": "1010101"}

shift_comp = {"D>>": "0010000", "A>>": "0000000", "M>>": "1000000",
              "D<<": "0110000", "A<<": "0100000", "M<<": "1100000"}


class AsmFile:
    def __init__(self, filename):
        # in case file is not of asm type
        if not filename.endswith(ASM_SUFFIX):
            raise AttributeError

        available_addresses = iter(range(16, Symbols['SCREEN'] - 1))
        self.variables = collections.defaultdict(available_addresses.__next__)
        self.labels = dict()

        with open(filename, 'r') as f:
            self.lines = self.pre_process(f)

    def pre_process(self, f):
        lines = []
        for line in f:
            clean_line = line.split("//")[0].strip()
            # if line is a label
            if clean_line.startswith("("):
                label_name = clean_line[1:-1]
                # line number is the value of the given label
                self.labels[label_name] = len(lines)
            # if line is an instruction, remove all spaces in line
            # and add it to the lines query of the file
            elif clean_line:
                lines.append(clean_line.replace(" ", ""))
            # if line is a comment (not part of the code)
            else:
                pass
        return lines

    def parse_address(self, address):
        if address in self.labels:
            return self.labels[address]
        if address in Symbols:
            return Symbols[address]
        else:
            return self.variables[address]

    def parse_a_instruction(self, line):
        try:
            address = int(line[1:])
        except ValueError:
            address = self.parse_address(line[1:])

        return "0{:0>15b}".format(address)

    @staticmethod
    def parse_c_instruction(line):
        inst_destination, comp_jump = line.split("=") if "=" in line else ("", line)
        inst_comp, inst_jump = comp_jump.split(";") if ";" in comp_jump else (comp_jump, "")

        # if the computation argument involves a shifting operation
        if inst_comp in shift_comp:
            return "101{}{}{}".format(shift_comp[inst_comp], destination[inst_destination],
                                      jump[inst_jump])

        return "111{}{}{}".format(comp[inst_comp], destination[inst_destination],
                                  jump[inst_jump])


if __name__ == '__main__':

    # create a list of all the files
    # in the directory (their absolute paths)
    path = sys.argv[1]
    current_directory = os.path.abspath(os.path.dirname(__file__))
    absolute_path = os.path.join(current_directory, path)
    if os.path.isdir(absolute_path):
        files_rudimentary = os.listdir(absolute_path)
        files = []
        for file in files_rudimentary:
            files.append(absolute_path + "/" + file)
    else:
        files = [os.path.abspath(path)]

    # iterate through all of the asm files and create
    # corresponding hack files with binary interpretation
    for file in files:
        try:
            Asm = AsmFile(file)
            hackFileName = file.replace(ASM_SUFFIX, HACK_SUFFIX)

            # for each of the lines, determine whether it
            # represents an A instruction or a C instruction
            with open(hackFileName, "a") as hackFile:
                for instruction in Asm.lines:
                    binaryLine = ""
                    if instruction.startswith(A_INSTRUCTION_PREFIX):
                        binaryLine = Asm.parse_a_instruction(instruction)
                    else:
                        binaryLine = Asm.parse_c_instruction(instruction)

                    hackFile.write(binaryLine + "\n")

        # if file is not an asm file,
        # continue on to the next file
        except AttributeError:
            continue
