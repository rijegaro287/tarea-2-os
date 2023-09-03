import { decodeResponseBody, sendImage, testAPI } from "./request.js";

document.addEventListener('DOMContentLoaded', async () => {
  const uploadButton = document.getElementById('upload-button') as HTMLButtonElement;
  const fileInput = document.getElementById('file-input') as HTMLInputElement;

  const uploadedImage = document.getElementById('uploaded-image') as HTMLImageElement;
  const processedImage = document.getElementById('processed-image') as HTMLImageElement;

  const processButton = document.getElementById('process-button') as HTMLButtonElement;
  const cancelButton = document.getElementById('cancel-button') as HTMLButtonElement;

  if (
    !uploadButton || !fileInput || !processButton ||
    !cancelButton || !uploadedImage || !processedImage
  ) {
    await alert('Error: Could not find all required elements. \nReloading...');
    return window.location.reload();
  }

  if (!fileInput.files) {
    processButton.disabled = true;
    cancelButton.disabled = true;
  }

  testAPI().then(async (response) => {
    if (response.status !== 200) {
      alert('Error: Could not connect to server.');
    }

    const responseBody = await decodeResponseBody(response);
    console.log(responseBody);
  });


  uploadButton.addEventListener('click', () => { fileInput.click() });


  fileInput.addEventListener('change', () => {
    if (!fileInput.files) { return; }

    const file = fileInput.files[0];
    uploadedImage.src = URL.createObjectURL(file);

    processButton.disabled = false;
    processButton.scrollIntoView();
  });


  processButton.addEventListener('click', () => {
    if (!fileInput.files) { return; }

    const image = fileInput.files[0];

    const reader = new FileReader();
    reader.readAsDataURL(image);

    reader.onload = async () => {
      const imageBase64 = reader.result as string;

      await sendImage(imageBase64)
        .then(async (response) => {
          if (response.status !== 200) {
            alert('Error: Could not upload file to server.');
          }

          const responseBody = await decodeResponseBody(response);
          console.log(responseBody);
        });
    }

  });
});