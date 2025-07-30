import './InputField.css';

interface InputFieldProps {
    label: string;
    type?: string;
    name: string;
    value: string;
    onChange: (e: React.ChangeEvent<HTMLInputElement>) => void;
    placeholder?: string;
}

export function InputField({ label, type = 'text', name, value, onChange, placeholder }: InputFieldProps) {
    return (
        <div className="input-field">
            <label htmlFor={name}>{label}</label>
            <input
                id={name}
                type={type}
                name={name}
                value={value}
                onChange={onChange}
                placeholder={placeholder}
            />
        </div>
    );
}
