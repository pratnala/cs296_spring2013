import re

text = open ('./doc/report_cs296_01.tex', 'r')
out1 = open ('./doc/profiling-report.html', 'w')
str1 = text.read ()
str1 = str1.replace ('\\pagebreak', '')
str1 = str1.replace ('~\\cite{see-saw}', '')
str1 = str1.replace ('~\\cite{free-body}', '')
str1 = str1.replace ('~\\cite{pendulum-motion}', '')
str1 = str1.replace ('~\\cite{google}', '')
str1 = str1.replace ('~\\cite{stackoverflow}', '')
str1 = str1.replace ('~\\cite{iforce2d}', '')
section_split = str1.split ('\section')
section_split = section_split[1:]
no_sections = len (section_split)
for i in range (0, no_sections):
	sub_split = section_split[i].split ('\subsection')
	no_sub = len (sub_split)
	for j in range (0, no_sub):
		subsub_split = sub_split[j].split ('\subsubsection')
		no_subsub = len (subsub_split)
		for k in range (0, no_subsub):
			flag = 0
			element = ''
			find_img = re.findall (r'\\begin{figure}[\x00-\xFF]*\\end{figure}', subsub_split[k])
			content_no_img = re.sub (r'\\begin{figure}[\x00-\xFF]*\\end{figure}', '', subsub_split[k])
			if find_img != []:
				img_name_list = re.findall (r'[-a-zA-Z0-9\_]*.png', find_img[0])
				caption_list = find_img[0].split ('\caption')
				caption_1 = re.findall (r'{[a-zA-Z ,()]*}\n', caption_list[1])
				caption_2 = caption_1[0]
				caption = caption_2[1:-2]
				no_imgs = len (img_name_list)
				for m in range (no_imgs):
					out1.write ('<img src = "screenshots/' + img_name_list[m] + '" width = "50%" align = "center"/>')
				out1.write ('<h2 align = "center">' + caption + '</h2>')
			element_length = len (content_no_img)
			for l in range (0, element_length):
				if flag == 0:
					if content_no_img[l] == '{':
						continue
					elif content_no_img[l] == '}':
						flag = 1
						break
					else:
						element = element + content_no_img[l]
			if j == 0:
				out1.write ('<h1>' + element + '</h1>')
				out1.write ('<p align = "justify">' + content_no_img[len (element) + 2:] + '</p>')
			else:
				if k == 0:
					out1.write ('<h2>' + element + '</h2>')
					out1.write ('<p align = "justify">' + content_no_img[len (element) + 2:] + '</p>')
				else:
					out1.write ('<h3>' + element + '</h3>')
					out1.write ('<p align = "justify">' + content_no_img[len (element) + 2:] + '</p>')

