import cv2
import numpy as np

def detect_foreground_objects(image_path, output_file):
    # Đọc ảnh
    image = cv2.imread(image_path)
    if image is None:
        print("Không thể đọc file ảnh. Hãy kiểm tra lại đường dẫn!")
        return

    # Lưu kích thước gốc
    original_height, original_width = image.shape[:2]

    # Resize ảnh (nếu cần) để dễ xử lý
    scale_percent = 50  # Resize ảnh xuống 50% kích thước gốc
    new_width = int(original_width * scale_percent / 100)
    new_height = int(original_height * scale_percent / 100)
    dim = (new_width, new_height)
    resized_image = cv2.resize(image, dim, interpolation=cv2.INTER_AREA)

    # Chuyển sang không gian màu HSV (để dễ phân đoạn màu)
    hsv = cv2.cvtColor(resized_image, cv2.COLOR_BGR2HSV)

    # Xác định màu nền (giả sử vùng nền chiếm diện tích lớn nhất)
    hist = cv2.calcHist([hsv], [0, 1], None, [180, 256], [0, 180, 0, 256])
    background_hue, background_saturation = np.unravel_index(np.argmax(hist), hist.shape)

    # Tạo mặt nạ cho các pixel khác màu nền
    lower_bound = np.array([background_hue - 10, max(0, background_saturation - 40), 0])
    upper_bound = np.array([background_hue + 10, min(255, background_saturation + 40), 255])
    mask = cv2.inRange(hsv, lower_bound, upper_bound)
    foreground_mask = cv2.bitwise_not(mask)

    # Tìm các contours của vật thể trong mặt nạ
    contours, _ = cv2.findContours(foreground_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Tính tỉ lệ scale để đưa về kích thước gốc
    scale_x = original_width / new_width
    scale_y = original_height / new_height

    # Ghi thông tin vào file txt
    with open(output_file, 'w') as file:
        for i, contour in enumerate(contours):
            # Lấy bounding box từ ảnh đã scale
            x, y, w, h = cv2.boundingRect(contour)

            # Đưa tọa độ và kích thước về kích thước gốc
            x_original = int(x * scale_x)
            y_original = int(y * scale_y)
            w_original = int(w * scale_x)
            h_original = int(h * scale_y)

            file.write(f"Vật thể {i + 1}: Tọa độ (x={x_original}, y={y_original}), Kích thước (w={w_original}, h={h_original})\n")
            print(f"Vật thể {i + 1}: Tọa độ (x={x_original}, y={y_original}), Kích thước (w={w_original}, h={h_original})")

            # Vẽ bounding box trên ảnh gốc
            cv2.rectangle(image, (x_original, y_original), 
                          (x_original + w_original, y_original + h_original), (0, 255, 0), 2)
            cv2.putText(image, f"{i + 1}", (x_original, y_original - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)

    # Hiển thị kết quả
    cv2.imshow("Original Image with Bounding Boxes", image)
    cv2.imshow("Foreground Mask", foreground_mask)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

# Gọi hàm
image_path = '/Users/holamngocbao/Desktop/abc_py/Map3.png'
output_file = '/Users/holamngocbao/Desktop/abc_py/output.txt'
detect_foreground_objects(image_path, output_file)
