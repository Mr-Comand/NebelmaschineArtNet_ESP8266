import os

def add_newline_escape(content):
    return '\\n\\\n'.join(content.splitlines())

def list_files_in_folder(folder_path):
    files = [f for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f))]
    return files

def generate_css_ino_file(input_path, output_path):
    # Read the css file
    css_file_path = os.path.join(input_path, "web", "main.css")
    with open(css_file_path, 'r') as css_file:
        css_content = css_file.read()

    # Format the css content
    css_content = css_content.replace("\\","\\\\").replace("\"","\\\"")
    formatted_content = '\\n\\\n'.join(css_content.splitlines())

    # Create the output INO file
    ino_file_path = os.path.join(output_path, "main", "main_css.ino")
    with open(ino_file_path, 'w') as ino_file:
        ino_file.write(f'#define main_css_code "{formatted_content}"')

    print(f'Successfully generated {ino_file_path}')
    


def generate_html_ino_file(input_path, output_path):
    # Read the html file
    html_file_path = os.path.join(input_path, "web", "index.html")
    with open(html_file_path, 'r') as html_file:
        html_content = html_file.read()

    # Format the html content
    html_content = html_content.replace("\\","\\\\").replace("\"","\\\"")
    formatted_content = '\\n\\\n'.join(html_content.splitlines())

    # Create the output INO file
    ino_file_path = os.path.join(output_path, "main", "index_html.ino")
    with open(ino_file_path, 'w') as ino_file:
        ino_file.write(f'#define index_html_code "{formatted_content}"')

    print(f'Successfully generated {ino_file_path}')
def generate_html_ino_file(input_path, input_name, output_path):
    # Read the html file
    html_file_path = os.path.join(input_path, input_name)
    with open(html_file_path, 'r') as html_file:
        html_content = html_file.read()

    # Format the html content
    html_content = html_content.replace("\\","\\\\").replace("\"","\\\"")
    formatted_content = '\\n\\\n'.join(html_content.splitlines())

    # Create the output INO file
    ino_file_path = os.path.join(output_path, input_name.replace(".","_").replace("-","_")+".h")
    with open(ino_file_path, 'w') as ino_file:
        ino_file.write(f'''
#ifndef {input_name.replace(".","_").replace("-","_")}_H
#define {input_name.replace(".","_").replace("-","_")}_H

#define {input_name.replace(".","_").replace("-","_")}_code "{formatted_content}"

#endif // {input_name.replace(".","_").replace("-","_")}_H
''')

    print(f'Successfully generated {ino_file_path}') 
if __name__ == "__main__":
    files = list_files_in_folder("web")
    for file in files:
        generate_html_ino_file("web", file, "main")




