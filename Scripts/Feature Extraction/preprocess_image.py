from argparse import ArgumentParser


def parse_arguments():
    """
    Parse Arguments from the command line
    """
    p = ArgumentParser(prog='preprocess_image')
    p.add_argument('-f', '--file', default='image_1.txt',
                   help='Path of file to be preprocessed')
    p.add_argument('-m', '--method', choices=['rga', 'tag'],
                   default='tag', help='Preprocess for RGA or Tagging')
    p.add_argument('-i', '--index', type=str, default=0,
                    help='index of image')
    p.add_argument('-l', '--length', type=int, default=1600,
                   help='Length of image')
    p.add_argument('-b', '--breadth', type=int, default=1200,
                   help='Breadth of image')
    p.add_argument('-o', default='image_1.h', dest='output_file')
    args = p.parse_args()
    return args


def preprocess_rga(lines, write_lines, length):
    """
    Edit write_lines so that it will give padded image needed for RGA
    """
    zero_line = ['0'] * (length + 2)
    zero_line = ",".join(zero_line)
    zero_line = '    {%s}' % zero_line

    write_lines.append('%s,\n' % zero_line)
    for idx, line in enumerate(lines):
        string = '    {0,%s,0},\n' % line[:-1]
        write_lines.append(string)
    write_lines.append('%s\n' % zero_line)
    write_lines.append('};')
    return write_lines


def preprocess_tagging(lines, write_lines):
    """
    Edit write_lines so that it will give non-padded image needed for Tagging
    """
    for idx, line in enumerate(lines):
        if idx == (len(lines) - 1):
            string = '    {%s}\n' % line[:-1]
        else:
            string = '    {%s},\n' % line[:-1]
        write_lines.append(string)
    write_lines.append('};')
    return write_lines


def init_write_lines(length, breadth):
    """
    Initialize write_lines
    """
    write_lines = [
        '#include "stdio.h"\n',
        '\n',
        f'#define LENGTH {length}\n',
        f'#define BREADTH {breadth}\n'
    ]
    return write_lines


def set_method(lines, write_lines, method, length, index):
    """
    Set appropriate method for preprocessing image
    """
    if method == 'tag':
        write_lines.append(
            f('short arr_out_img_{index}[BREADTH][LENGTH] = {\n')
        )
        write_lines = preprocess_tagging(lines, write_lines)
    else:
        write_lines.append(
            'short arr_out_img_%s[BREADTH + 2][LENGTH + 2] = {\n'%(index)
        )
        write_lines = preprocess_rga(lines, write_lines, length)
    return write_lines


def main():
    args = parse_arguments()
    with open(args.file) as f:
        lines = f.readlines()

    write_lines = init_write_lines(args.length, args.breadth)
    set_method(lines, write_lines, args.method, args.length, args.index)

    write_f = open(args.output_file, 'w')
    write_f.writelines(write_lines)
    write_f.close()


if __name__ == '__main__':
    main()
