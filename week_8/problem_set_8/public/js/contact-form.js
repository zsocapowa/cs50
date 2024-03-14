export function loadFormData() {
    const location = window.location.pathname;
    if (location != '/contact') {
        return;
    }
    const storedData = localStorage.getItem('formData');

    if (storedData) {
        const formData = JSON.parse(storedData);

        for (const [key, value] of Object.entries(formData)) {
            document.querySelector(`#${key}`).value = value
        }
    }
};


document.addEventListener("change", (e) => {
    const { target } = e;
    if (!target.matches("#contact-form input")) {
        return;
    }
    e.preventDefault();
    saveFormData(target)
});


function saveFormData(target) {
    let formData = {};
    const storedData = localStorage.getItem('formData');
    if (storedData === null) {
        formData[target.id] = target.value;
    }
    else {
        formData = JSON.parse(storedData);
        formData[target.id] = target.value;
    }
    localStorage.setItem('formData', JSON.stringify(formData));
}

