# TT-VXL
Thư viện của thầy Hoàn: https://github.com/PhanHoan/TTVXL_ST2/tree/2_Nhat_Cuong

Có một số bài mình dùng hàm kiểm tra nút nhấn khác với hàm của thầy, cách của mình có nhược điểm
so với hàm của thầy là chỉ biết được lúc nhấn nhưng không có hiệu ứng nhấn giữ.
Còn các hiệu ứng khác thì vẫn đáp ứng tốt, như chống dội, hay không làm gián đoạn chương trình chính.

Phương pháp:

- Dùng 1 biến 16bit để kiểm tra giá trị của ngõ vào nút nhấn
- Kiểm tra biến đó tùy vào nút nhấn tích cực mức cao hoặc mức thấp rồi xử lý công việc cần thực
hiện.

Cách dùng như sau:

- Khai báo biến 16bit:

	unsigned int16 Up_state = 0;

- Trong hàm while(true) thì liên lục kiểm tra ngõ vào của nút nhấn bằng cách or với hàm INPUT

	Up_state = (Up_state<<1) | input(UP);
	
- Sau đó kiểm tra biến Up_state

	If(Up_state == 0x8000){ // 0x8000 = 1000 0000 0000 0000
	
		// công việc cần thực hiện

	}
	
Giải sử nút nhấn tích cực mức cao( được nối lên nguồn qua trở):
![image](https://user-images.githubusercontent.com/94792322/219923014-4f399588-afa8-4901-b78b-b7bdea871a29.png)

