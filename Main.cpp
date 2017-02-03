#include <Siv3D.hpp>
#include <sstream>
#include <vector>
#include <string>
#include <exception>
#include <Windows.h>

String filename_return(String &str) {
	auto rev = str.reverse();
	rev = rev.substr(4);
	auto ret = rev.reverse();

	return ret;
}

void Main()
{

	while (true) {

		const Font font(15);
		Array<FilePath> items;
		Window::Resize(800, 600);
		Window::SetTitle(L"heatmapviewer");
		while (System::Update())
		{
			font(L"画像ファイルをドロップして\n同じ場所に同じ名前のcsvも用意して\n").draw();
			if (Dragdrop::HasItems())
			{
				// ドロップされたすべてのアイテムを取得
				items = Dragdrop::GetFilePaths();
				break;
			}
			if (Input::KeyQ.clicked) {
				return;
			}
		}

		String filename = *(items.begin());
		String csvfilename = filename_return(filename) + L".csv";
		Image img(filename);
		Texture tex(img);
		CSVReader reader(csvfilename);

		if (!reader) {
			while (System::Update()) {
				font(L"csvないから終了するね\n").draw();
				WaitKey();
				return;
			}
			
		}


		Window::Resize(tex.width, tex.height);


		int32 i = 0;
		int32 x, y;
		while (System::Update())
		{
			tex.draw();
			x = reader.get<int32>(i, 0);
			y = reader.get<int32>(i, 1);

			Circle(x, y, 30).draw(Color(255, 0, 0, 127));
			i++;
			if (Input::KeyQ.clicked) {
				
				return;
			}
			if (i >= reader.rows) {
				break;
			}
		}

	}
}
